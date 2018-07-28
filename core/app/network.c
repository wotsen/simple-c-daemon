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
#include <json-c/json.h>

#include "../module/module.h"
#include "../common/common.h"
#include "protocol.h"
#include "def_paras.h"
#include "def_network.h"

struct json_object *pack_heart_beat(void)
{
    struct json_object *heart = NULL;
    class_module *module;
    class_para *para;
    class_para_head heart_id = KEY_HEART_BEAT;

    module = get_module_by_id(ID_NETWORK);
    para = get_para_by_id(module->para_table, heart_id);
    heart = packet_json(module);

    json_object_set_int(
            json_object_object_get(
                json_object_object_get(heart, "module"), "module-len"),
            1);
    json_object_set_int(
            json_object_object_get(
                json_object_object_get(heart, "module"), "module-cmd"), 
            HEART_CMD);

    json_object_object_add(heart, "key-1", 
            pack_json_para(para, (char *)"daemon heart beat"));

    pack_key_end(heart);

    return heart;
}

void network_initial()
{
    udp_net_initial();
    put_udp_task(pack_heart_beat);
}
