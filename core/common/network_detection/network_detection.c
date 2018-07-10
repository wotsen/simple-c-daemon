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

#include "../../module/module.h"
#include "../common.h"

#define MAX_UDP_TASK        64

unsigned short g_local_udp_port = DAEMON_SERVER_PORT;
unsigned short g_application_udp_port = APPLICATION_PORT;
unsigned short g_local_ssl_port = DAEMON_SSL_PORT;
unsigned short g_application_ssl_port = APPLICATION_SSL_PORT;

static int s_socket = -1;
static char udp_buf[NET_DATA_LEN_MAX];
static struct json_object *(*udp_send_task[MAX_UDP_TASK])(void) = {NULL};

bool put_udp_task(struct json_object *(*fun)(void))
{
    int i = 0;
    for(i = 0; i < MAX_UDP_TASK; i++)
    {
        if(NULL == udp_send_task[i])
        {
            udp_send_task[i] = fun;
            return true;
        }
    }
    return false;
}

bool del_udp_task(struct json_object *(*fun)(void))
{
    int i = 0;
    for(i = 0; i < MAX_UDP_TASK; i++)
    {
        if(fun == udp_send_task[i])
        {
            udp_send_task[i] = NULL;
            return true;
        }
    }
    return false;
}

void clean_udp_task(void)
{
    int i = 0;
    for(i = 0; i < MAX_UDP_TASK; i++)
    {
        if(NULL != udp_send_task[i])
        {
            udp_send_task[i] = NULL;
        }
    }
}

static void send_udp_packet(struct json_object *obj_send)
{
    size_t len = 0;
    char *send_js_str = (char *)json_object_to_json_string_length(obj_send, JSON_C_TO_STRING_NOSLASHESCAPE, &len);

    //dbg_print("heart-beat : %s", json_object_to_json_string_ext(obj_send, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));
    dbg_print("%s  | str_len = %d, real_len = %d", send_js_str, len, strlen(send_js_str));

    m_udpsock_send(s_socket, NULL, g_application_udp_port, send_js_str, len);
    json_object_put(obj_send);
}

void poll_udp_task(void)
{
    int i = 0;
    struct json_object *obj_send = NULL;

    for(i = 0; i < MAX_UDP_TASK; i++)
    {
        if(NULL != udp_send_task[i])
        {
            obj_send = udp_send_task[i]();
            send_udp_packet(obj_send);
        }
    }
}

int recv_udp_data(struct sockaddr_in *sin)
{
    int len = sizeof(struct sockaddr);
    memset(sin, 0, sizeof(struct sockaddr_in));
    len = recvfrom(s_socket, udp_buf, sizeof(udp_buf), 0, (struct sockaddr *)sin, (socklen_t *)&len);
    return len;
}


static void deal_udp_data(int len, struct sockaddr_in sin)
{
    struct json_object *obj_recv = NULL;
    enum json_tokener_error error;
    obj_recv = json_tokener_parse_verbose(udp_buf, &error);
    if(error != json_tokener_success)
    {
        dbg_error("udp recv error : [%d]", error);
        return;
    }
    dbg_print("recv : %s", json_object_to_json_string_ext(obj_recv, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));
    json_object_put(obj_recv);
}

static bool check_recv_udp_data(int len)
{
    if(len > 0)
    {
        return true;
    }
    else if(len == -1)
    {
        if(errno != EAGAIN)
        {
            close(s_socket);
            s_socket = -1;
            m_ostime_delay(OS_SEC(2));
        }
    }
    return false;
}

static int create_udp_simple(void)
{
    return m_udpsock_create(NULL, NULL, g_local_udp_port, 2, 5);
}

static void network_task(void)
{
    int len;
    struct sockaddr_in sin;
    for(;;)
    {
        if(s_socket < 0)
        {
            if((s_socket = create_udp_simple()) < 0){
                m_ostime_delay(OS_SEC(2));
                continue;
            }
        }
        poll_udp_task();
        len = recv_udp_data(&sin);
        if(check_recv_udp_data(len))
        {
            deal_udp_data(len, sin);
        }
        m_ostime_delay(OS_SEC(5));
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
