/*
 * =====================================================================================
 *
 *       Filename:  protocol.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/08/2018 02:41:20 PM
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
#include <inttypes.h>

#include "../module/module.h"
#include "../common/common.h"
#include "protocol.h"

/*
 * 数据包格式:
 * "head":{
 *      "os-type": ,
 *      "hostnme": ,
 *      "os-release": ,
 *      "os-version": ,
 *      "os-machine": ,
 *      "cur-time": 
 * },
 * "module":{
 *      "src": ,
 *      "dest": ,
 *      "module-name": ,
 *      "module-id": ,
 *      "len": ,
 *      "ack": ,
 *      "cmd": 
 * },
 * "key-1":{
 *      "key-name": ,
 *      "key-id": ,
 *      "key-len": ,
 *      "key-type": ,
 *      "key-context":
 * },
 * "key-end":{
 *      "key": "end"
 * }
 *
 * 
 * */

static const struct os_base_info system_uname[] = {
    {"os-type",     os_type},
    {"hostnme",     hostname},
    {"os-release",  os_release},
    {"os-version",  os_version},
    {"os-machine",  os_machine},
    {NULL, NULL}
};

struct json_object *pack_key_end(struct json_object *packet)
{
    struct json_object *key_end = json_object_new_object();

    json_object_object_add(key_end, "key", json_object_new_string("end"));
    json_object_object_add(packet, "key-end", key_end);

    return packet;
}

struct json_object *pack_json_para(class_para *para, char *val)
{
    struct json_object *key = json_object_new_object();
    char   str[256];

    json_object_object_add(key, "key-name", 
                           json_object_new_string(para->id.name));
    json_object_object_add(key, "key-id", 
                           json_object_new_int(para->id.id));
    json_object_object_add(key, "key-len", 
                           json_object_new_int(para->len));
    json_object_object_add(key, "key-type", 
                           json_object_new_int(para->type));
    
    if (!para->len) { return key; }

    switch (para->type) {
        case __bool:
            json_object_object_add(
                        key, 
                        "context",
                        json_object_new_string(*val ? "true" : "false"));
            break;
        case __char:
            json_object_object_add(
                        key,
                        "context", 
                        json_object_new_int(*val));
            break;
        case __uchar:
            json_object_object_add(
                        key,
                        "context", 
                        json_object_new_int(*((uint8_t*)val)));
            break;
        case __short:
            json_object_object_add(
                        key,
                        "context", 
                        json_object_new_int(*((int16_t*)val)));
            break;
        case __ushort:
            json_object_object_add(
                        key,
                        "context", 
                        json_object_new_int(*((uint16_t*)val)));
            break;
        case __int:
            json_object_object_add(
                        key,
                        "context", 
                        json_object_new_int(*((int32_t*)val)));
            break;
        case __uint:
            json_object_object_add(
                        key,
                        "context", 
                        json_object_new_int(*((uint32_t*)val)));
            break;
        case __long:
            json_object_object_add(
                        key,
                        "context", 
                        json_object_new_int(*((long*)val)));
            break;
        case __ulong:
            json_object_object_add(
                        key,
                        "context", 
                        json_object_new_int(*((unsigned long*)val)));
            break;
        case __llong:
            json_object_object_add(
                        key,
                        "context", 
                        json_object_new_int64(*((long long*)val)));
            break;
        case __ullong:
            json_object_object_add(
                        key,
                        "context", 
                        json_object_new_int64(*((unsigned long long*)val)));
            break;
        case __double:
            json_object_object_add(
                        key,
                        "context", 
                        json_object_new_double(*((double*)val)));
            break;
        default:
            sprintf(str, "%s", val);
            json_object_object_add(
                        key,
                        "context", 
                        json_object_new_string(str));
            break;
    }

    return key;
}

struct json_object *pack_json_head()
{
    int32_t i = 0;
    char    time[256];
    struct json_object *obj  = json_object_new_object();
    struct json_object *hobj = json_object_new_object();

    memset(time, 0, sizeof(time));
    getostimestr(time);

    for (i = 0; NULL != system_uname[i].key; i++) {
        json_object_object_add(
                               hobj,
                               system_uname[i].key, 
                               json_object_new_string(system_uname[i].get()));
    }
    json_object_object_add(hobj, "cur-time", json_object_new_string(time));
    json_object_object_add(obj, "head", hobj);

    return obj;
}

struct json_object *pack_json_module(
                    struct json_object *packet,
                    class_module *module)
{
    struct json_object *mobj = json_object_new_object();

    json_object_object_add(mobj,
                           "src",
                           json_object_new_string("none"));
    json_object_object_add(mobj,
                           "dest", 
                           json_object_new_string("none"));
    json_object_object_add(mobj,
                           "module-name",
                           json_object_new_string(module->section));
    json_object_object_add(mobj,
                           "module-id",
                           json_object_new_int(module->id));
    json_object_object_add(mobj,
                           "module-len",
                           json_object_new_int(0));
    json_object_object_add(mobj,
                           "module-ack",
                           json_object_new_int(ACK_INIT));
    json_object_object_add(mobj,
                           "module-cmd",
                           json_object_new_int(0));

    json_object_object_add(packet, "module", mobj);

    return packet;
}

struct json_object *packet_json(class_module *module)
{
    struct json_object *packet = pack_json_head();

    pack_json_module(packet, module);

    return packet;
}


bool unpack_json_head(struct json_object *packet)
{
    struct json_object *head = json_object_object_get(packet, "head");
    struct json_object *module = json_object_object_get(packet, "module");

    if (!head || !module) { return false; }

    return unpack_json_module(packet, module);
}

bool unpack_json_module(struct json_object *packet, struct json_object *module)
{
    bool    ret = true;
    int32_t len = 0;
    int32_t i   = 1;
    char    key_name[125];
    struct  json_object *key     = NULL;
    struct  json_object *key_len = NULL;

    if (!(key_len = json_object_object_get(module, "len"))) {
        return false;
    }
    if (!(len = json_object_get_int(key_len))) { return false; }

    do {
        sprintf(key_name, "key-%d", i);
        if (!(key = json_object_object_get(packet, (const char *)key_name))) {
            return false;
        }
        if (!unpack_json_key(packet, module, key)) {
            ret = false;
        }

        i++;

    }while(i <= len);

    return ret;
}

bool unpack_json_key(struct json_object *packet,
                     struct json_object *module, 
                     struct json_object *key)
{
    return true;
}

