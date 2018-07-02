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
#include <json-c/json.h>

#include "../../module/module.h"
#include "network_protocol.h"
#include "../common.h"

static int s_socket = -1;

static char udp_buf[NET_DATA_LEN_MAX];

struct class_poll{
    char *data;
    unsigned int len;
};

struct class_normal_daemon{
    unsigned int length;
    unsigned char cmd;
    char name[128];
    unsigned char ip[4];
    char time[0];
}PACKED;

static struct class_poll test_send = {
    "daemon heart",
    12
};

void send_udp_data(char *data, unsigned int len)
{
    m_udpsock_send(s_socket, NULL, VER_CENTER_PORT, data, len);
}

int recv_udp_data(struct sockaddr_in *sin)
{
    int len = sizeof(struct sockaddr);
    memset(sin, 0, sizeof(struct sockaddr_in));
    len = recvfrom(s_socket, udp_buf, sizeof(udp_buf), 0, (struct sockaddr *)sin, (socklen_t *)&len);
    return len;
}

static void send_normal_packet(void)
{
    struct class_normal_daemon *send;
    send = (struct class_normal_daemon *)m_memory_alloc(1024);
    free(send);

    size_t len = 0;
    struct json_object *obj_send = json_object_new_object();
    json_object_object_add(obj_send, "pro-name", json_object_new_string("daemon"));
    json_object_object_add(obj_send, "content", json_object_new_string("sync pack"));

    char *send_js_str = (char *)json_object_to_json_string_length(obj_send, JSON_C_TO_STRING_NOSLASHESCAPE, &len);

    m_udpsock_send(s_socket, NULL, 9567, send_js_str, len);
    json_object_put(obj_send);

    return;
}

static int create_udp_simple(void)
{
    return m_udpsock_create(NULL, NULL, DAEMON_SERVER_PORT, 2, 5);
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

static bool check_udp_data_crc(int len)
{
    unsigned short crc = 0;
    memcpy(&crc, &udp_buf[len-2], 2);
    return true;
}

static class_pack_head *unpack_udp_data(int len)
{
    class_pack_head *packet = NULL;
    if(!check_udp_data_crc(len))
    {
        return NULL;
    }

    packet = (class_pack_head *)m_memory_alloc(NET_DATA_LEN_MAX);
    memcpy(packet, udp_buf, len-2);

    if(((len - packet->len) != 2) ||
            packet->ack != ACK_INIT)
    {
        free(packet);
        return NULL;
    }
    return packet;
}

static void deal_udp_data(int len, struct sockaddr_in sin)
{
    class_pack_head *packet = NULL;

    if(len < (PACK_HEAD_LEN + 2))
    {
        return;
    }
    if(NULL == (packet = unpack_udp_data(len)))
    {
        return;
    }
    switch(packet->module){
        case LOCAL_SYNC_MODULE:
            break;
        case NET_SYNC_MODULE:
            break;
        default:
            break;
    }
    dbg_print("udp-recv : ip = %s port = %d | %s", &sin.sin_addr.s_addr, ntohs(sin.sin_port), udp_buf);
    free(packet);
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
        send_normal_packet();
        send_udp_data(test_send.data, test_send.len);
        len = recv_udp_data(&sin);
        if(check_recv_udp_data(len))
        {
            deal_udp_data(len, sin);
        }
        m_ostime_delay(OS_SEC(5));
    }
}

void network_start(void)
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, (void *)network_task, NULL);
}
