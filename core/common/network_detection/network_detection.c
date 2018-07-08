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
unsigned short g_local_udp_port = DAEMON_SERVER_PORT;
unsigned short g_application_udp_port = APPLICATION_PORT;
unsigned short g_local_ssl_port = DAEMON_SSL_PORT;
unsigned short g_application_ssl_port = APPLICATION_SSL_PORT;

static char udp_buf[NET_DATA_LEN_MAX];

struct class_normal_daemon{
    unsigned int length;
    unsigned char cmd;
    char name[128];
    unsigned char ip[4];
    char time[0];
}PACKED;

int recv_udp_data(struct sockaddr_in *sin)
{
    int len = sizeof(struct sockaddr);
    memset(sin, 0, sizeof(struct sockaddr_in));
    len = recvfrom(s_socket, udp_buf, sizeof(udp_buf), 0, (struct sockaddr *)sin, (socklen_t *)&len);
    return len;
}

struct msg_module_info {
    const char *key;
    char content[20];
};

static struct msg_module_info heart_module[] = {
    {"module-name", "heart beat"},
    {"module-id", "0x1"},
    {"msg-ack", "none"},
    {"msg-cmd", "none"},
    {NULL, {0}}
};


struct os_base_info {
    const char *key;
    char *(*get)();
};

static const struct os_base_info system_uname[] = {
    {"os-type", os_type},
    {"hostnme", hostname},
    {"os-release", os_release},
    {"os-version", os_version},
    {"os-machine", os_machine},
    {NULL, NULL}
};


static struct json_object *pack_json_head(struct msg_module_info *module)
{
    int i = 0;
    char time[256];
    struct json_object *obj = json_object_new_object();
    struct json_object *hobj = json_object_new_object();

    memset(time, 0, sizeof(time));
    m_getostimestr(time);

    for(i = 0; NULL != system_uname[i].key; i++)
    {
        json_object_object_add(hobj, system_uname[i].key, json_object_new_string(system_uname[i].get()));
    }
    json_object_object_add(hobj, "cur-time", json_object_new_string(time));

    json_object_object_add(obj, "head", hobj);
    for(i = 0; NULL != module[i].key; i++)
    {
        json_object_object_add(obj, module[i].key, json_object_new_string(module[i].content));
    }

    return obj;
}

static void send_normal_packet(void)
{
    size_t len = 0;
    struct json_object *obj_send = pack_json_head(heart_module);

    char *send_js_str = (char *)json_object_to_json_string_length(obj_send, JSON_C_TO_STRING_NOSLASHESCAPE, &len);

    //dbg_print("heart-beat : %s", json_object_to_json_string_ext(obj_send, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));
    //dbg_print("%s  | str_len = %d, real_len = %d", send_js_str, len, strlen(send_js_str));

    m_udpsock_send(s_socket, NULL, g_application_udp_port, send_js_str, len);
    json_object_put(obj_send);

    return;
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
        send_normal_packet();
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
