/*
 * =====================================================================================
 *
 *       Filename:  network.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/10/2018 10:37:48 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <json-c/json.h>

#include "../module/module.h"
#include "../common/common.h"
#include "protocol.h"
#include "def_network.h"
#include "def_paras.h"

struct json_object *pack_heart_beat(void)
{
    struct json_object *heart   = NULL;
    class_module       *module;
    class_para         *para;
    class_para_head    heart_id = KEY_HEART_BEAT;

    module = get_module_by_id(ID_NETWORK);
    para = get_para_by_id(module->para_table, heart_id);
    heart = pack_json(module);

    json_object_set_int(
            json_object_object_get(
                json_object_object_get(heart, STR_MODULE),
                STR_MODULE_LEN),
            1);
    json_object_set_int(
            json_object_object_get(
                json_object_object_get(heart, STR_MODULE),
                STR_MODULE_CMD), 
            HEART_CMD);

    json_object_object_add(
            heart,
            STR_KEY_NEXT"1", 
            pack_json_para(para, (char *)"daemon heart beat"));

    pack_key_end(heart);

    return heart;
}

static void *network_task(void* arg)
{
    if (arg) {};
    struct json_object *recv = NULL;
    for ( ; ;){
        if (!(recv = pop_udp_data_list())) {
            ostime_delay(OS_SEC(1));
            continue;
        }
#if 0
        dbg_print("recv : %s", 
                json_object_to_json_string_ext(
                    recv, 
                    JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));
#endif
        unpack_json(recv);
        recv = NULL;
    }
    return ((void *)0);
}
void network_initial()
{
    udp_net_initial();
    //put_udp_task(pack_heart_beat);
}

static void udp_network_start(void)
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, &udp_network_task, NULL);
}

void network_start(void)
{
    pthread_t thread_id;

    udp_network_start(); 
    pthread_create(&thread_id, NULL, &network_task, NULL);
}
