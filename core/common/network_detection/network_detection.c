/******************************************    *******************************

  > File Name: network_detection.c

  > Author: Ywl

  > Descripsion:

  > Created Time:     Mon 07 May 2018 09:54:29 PM CST

  > Modify Time: 

 *********************************    ***************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <inttypes.h>

#include "../../module/module.h"
#include "../../module/list.h"
#include "../common.h"

#define MAX_UDP_TASK        64

uint16_t g_local_udp_port = DAEMON_SERVER_PORT;
uint16_t g_application_udp_port = APPLICATION_PORT;
uint16_t g_local_ssl_port = DAEMON_SSL_PORT;
uint16_t g_application_ssl_port = APPLICATION_SSL_PORT;

static int32_t _s_socket = -1;
static char _udp_buf[NET_DATA_LEN_MAX];
static udp_task_function _udp_send_task[MAX_UDP_TASK] = {NULL};

bool put_udp_task(udp_task_function fun)
{
    int32_t i = 0;
    for (i = 0; i < MAX_UDP_TASK; i++) {
        if (!_udp_send_task[i]) {
            _udp_send_task[i] = fun;
            return true;
        }
    }
    return false;
}

bool del_udp_task(struct json_object *(*fun)(void))
{
    int32_t i = 0;
    for (i = 0; i < MAX_UDP_TASK; i++) {
        if (fun == _udp_send_task[i]) {
            _udp_send_task[i] = NULL;
            return true;
        }
    }
    return false;
}

void clean_udp_task(void)
{
    int32_t i = 0;
    for (i = 0; i < MAX_UDP_TASK; i++) {
        _udp_send_task[i] = NULL;
    }
}


static void send_udp_packet(struct json_object *obj_send)
{
    size_t len = 0;
    char *send_js_str = (char *)json_object_to_json_string_length(
            obj_send, 
            JSON_C_TO_STRING_NOSLASHESCAPE, &len);

#ifdef dbg
    dbg_print("heart-beat : %s", 
            json_object_to_json_string_ext(
                obj_send, 
                JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));
#endif
#if DEBUG_MONITOR
    dbg_print("%s  | str_len = %d, real_len = %d", 
            send_js_str, len, strlen(send_js_str));
#endif

    udpsock_send(_s_socket, NULL, g_application_udp_port, send_js_str, len);
    json_object_put(obj_send);
}

void poll_udp_task(void)
{
    int32_t i = 0;
    struct json_object *obj_send = NULL;

    for (i = 0; i < MAX_UDP_TASK; i++) {
        if (_udp_send_task[i]) {
            obj_send = _udp_send_task[i]();
            send_udp_packet(obj_send);
        }
    }
}

int32_t recv_udp_data(struct sockaddr_in *sin)
{
    int32_t len = sizeof(struct sockaddr);
    memset(sin, 0, sizeof(struct sockaddr_in));
    len = recvfrom(_s_socket, _udp_buf, sizeof(_udp_buf),
            0, (struct sockaddr *)sin, (socklen_t *)&len);
    return len;
}

LIST_HEAD(udp_recv_json_data);

void push_udp_data_list(struct json_object *recv)
{
    class_udp_recv_list *node = NULL;
    node->udp_data = recv;
    INIT_LIST_HEAD(&node->list);
    list_add(&node->list, &udp_recv_json_data);
}

struct json_object *pop_udp_data_list(void)
{
}

static void deal_udp_data(int32_t len, struct sockaddr_in sin)
{
    struct json_object *obj_recv = NULL;
    uint8_t ip[4];
    enum json_tokener_error error;

    memcpy(ip, &sin.sin_addr.s_addr, sizeof(ip));
    obj_recv = json_tokener_parse_verbose(_udp_buf, &error);
    if (error != json_tokener_success) {
        dbg_error("udp recv error : [%d], ip : [%d.%d.%d.%d], port : [%d]",
                ip[0], ip[1], ip[2], ip[3],
                sin.sin_port,
                error);
        udpsock_send(_s_socket, (char *)ip, sin.sin_port, _udp_buf, len);
        return;
    }
#if DEBUG_MONITOR
    dbg_print("recv : %s", 
            json_object_to_json_string_ext(
                obj_recv, 
                JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));
#endif
    push_udp_data_list(obj_recv);
    //json_object_put(obj_recv);
}

static bool check_recv_udp_data(int32_t len)
{
    if (len > 0) {
        return true;
    } else if (len == -1) {
        if (errno != EAGAIN) {
            close(_s_socket);
            _s_socket = -1;
            ostime_delay(OS_SEC(2));
        }
    }
    return false;
}

static int32_t create_udp_simple(void)
{
    return udpsock_create(NULL, NULL, g_local_udp_port, 2, 5);
}

static void network_task(void)
{
    int32_t len;
    struct sockaddr_in sin;
    for ( ; ;) {
        if (_s_socket < 0) {
            if ((_s_socket = create_udp_simple()) < 0){
                ostime_delay(OS_SEC(2));
                continue;
            }
        }
        poll_udp_task();
        len = recv_udp_data(&sin);
        if (check_recv_udp_data(len)) {
            deal_udp_data(len, sin);
        }
        ostime_delay(OS_SEC(5));
    }
}

void udp_net_initial(void)
{
    clean_udp_task();
}

void network_start(void)
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, (void *)network_task, NULL);
}
