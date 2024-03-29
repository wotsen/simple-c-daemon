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
#include "../common.h"

#define MAX_UDP_TASK        64

uint16_t g_local_udp_port = DAEMON_SERVER_PORT;
uint16_t g_application_udp_port = APPLICATION_PORT;
uint16_t g_local_ssl_port = DAEMON_SSL_PORT;
uint16_t g_application_ssl_port = APPLICATION_SSL_PORT;

static int32_t _s_socket = -1;
static char _udp_buf[NET_DATA_LEN_MAX];
static udp_task_function _udp_send_task[MAX_UDP_TASK] = {NULL};

void send_udp_packet(struct json_object *obj_send, uint8_t *ip, uint16_t port)
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
    udpsock_send(_s_socket, ip, port, send_js_str, len);
    json_object_put(obj_send);
}

static void send_udp_simple_packet(struct json_object *obj_send)
{
    send_udp_packet(obj_send, NULL, g_application_udp_port);
}


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


void poll_udp_task(void)
{
    int32_t i = 0;
    static int32_t _time = 0;
    getostime();
    struct json_object *obj_send = NULL;
    if ((getostime() - _time) < OS_MS(3)) { return; }
    for (i = 0; i < MAX_UDP_TASK; i++) {
        if (_udp_send_task[i]) {
            obj_send = _udp_send_task[i]();
            send_udp_simple_packet(obj_send);
        }
    }
    _time = getostime();
}

int32_t recv_udp_data(struct sockaddr_in *sin)
{
    int32_t len = sizeof(struct sockaddr);
    memset(sin, 0, sizeof(struct sockaddr_in));
    memset(_udp_buf, 0, sizeof(_udp_buf));
    len = recvfrom(_s_socket, _udp_buf, sizeof(_udp_buf),
            0, (struct sockaddr *)sin, (socklen_t *)&len);
    return len;
}

void set_addr_info(struct json_object *packet, uint8_t *ip, uint16_t port)
{
    struct json_object *addr = json_object_new_object();
    struct json_object *obj_ip = json_object_new_array();

    json_object_array_add(obj_ip, json_object_new_int(ip[0]));
    json_object_array_add(obj_ip, json_object_new_int(ip[1]));
    json_object_array_add(obj_ip, json_object_new_int(ip[2]));
    json_object_array_add(obj_ip, json_object_new_int(ip[3]));
    json_object_object_add(addr, STR_IP, obj_ip);
    json_object_object_add(addr, STR_PORT, json_object_new_int(port));
    json_object_object_add(packet, STR_ADDRESS, addr);
}
void get_addr_info_by_addr(struct json_object *addr, uint8_t *ip, uint16_t *port)
{
    ip[0] = json_object_get_int(
                json_object_array_get_idx(
                    json_object_object_get(addr, STR_IP), 
                    0));
    ip[1] = json_object_get_int(
                json_object_array_get_idx(
                    json_object_object_get(addr, STR_IP), 
                    1));
    ip[2] = json_object_get_int(
                json_object_array_get_idx(
                    json_object_object_get(addr, STR_IP), 
                    2));
    ip[3] = json_object_get_int(
                json_object_array_get_idx(
                    json_object_object_get(addr, STR_IP), 
                    3));
    *port = json_object_get_int(json_object_object_get(addr, STR_PORT));
}

void get_addr_info(struct json_object *packet, uint8_t *ip, uint16_t *port)
{
    struct json_object *addr   = json_object_object_get(packet, STR_ADDRESS);
    get_addr_info_by_addr(addr, ip, port);
}

static void div_udp_data(int32_t len, struct sockaddr_in sin)
{
    struct json_object *obj_recv = NULL;
    uint8_t ip[4];
    enum json_tokener_error error;

    memcpy(ip, &sin.sin_addr.s_addr, sizeof(ip));
    obj_recv = json_tokener_parse_verbose(_udp_buf, &error);
    if (error != json_tokener_success) {
        dbg_error("udp recv error : [%d], ip : [%d.%d.%d.%d], port : [%d]",
                error,
                ip[0], ip[1], ip[2], ip[3],
                ntohs(sin.sin_port));
        udpsock_send(_s_socket, ip, ntohs(sin.sin_port), _udp_buf, len);
        return;
    }
    set_addr_info(obj_recv, ip, ntohs(sin.sin_port));
    push_udp_data_list(obj_recv);
#if 0
#if DEBUG_MONITOR
    dbg_print("recv : %s", 
            json_object_to_json_string_ext(
                obj_recv, 
                JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));
#endif
#endif
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

void *udp_network_task(void* arg)
{
    if (arg) {};
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
            div_udp_data(len, sin);
        }
    }
    return ((void *)0);
}

void udp_net_initial(void)
{
    clean_udp_task();
}

