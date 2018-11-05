/*
 * =====================================================================================
 *
 *       Filename:  module_protocol.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/02/2018 02:58:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include "../module/module.h"
#include "../common/common.h"
#include "protocol.h"
#include "key_protocol.h"

struct json_object *pack_json_module(
                    struct json_object *packet,
                    class_module *module)
{
    struct json_object *mobj = json_object_new_object();

    json_object_object_add(mobj,
                           STR_MODULE_SRC,
                           json_object_new_string(JSON_STR_INI));
    json_object_object_add(mobj,
                           STR_MODULE_DEST, 
                           json_object_new_string(JSON_STR_INI));
    json_object_object_add(mobj,
                           STR_MODULE_NAME,
                           json_object_new_string(module->section));
    json_object_object_add(mobj,
                           STR_MODULE_ID,
                           json_object_new_int(module->id));
    json_object_object_add(mobj,
                           STR_MODULE_LEN,
                           json_object_new_int(0));
    json_object_object_add(mobj,
                           STR_MODULE_ACK,
                           json_object_new_int(ACK_INIT));
    json_object_object_add(mobj,
                           STR_MODULE_CMD,
                           json_object_new_int(0));

    json_object_object_add(packet, STR_MODULE, mobj);

    return packet;
}

static int32_t _get_key_len(struct json_object *module)
{
    int32_t len = 0;
    struct  json_object *key_len = NULL;

    if (!(key_len = json_object_object_get(module, STR_MODULE_LEN))) {
        return 0;
    }
    if (!(len = json_object_get_int(key_len))) { 
        return 0; 
    }
    return len;
}

static struct json_object *_get_module_obj_ack(struct json_object *module)
{
    struct  json_object *obj_ack = NULL;
    if (!(obj_ack = json_object_object_get(module, STR_MODULE_ACK))) {
        return NULL;
    }
    return obj_ack;
}

static void _set_module_ack(struct json_object *module, uint8_t ack)
{
    struct  json_object *obj_ack = _get_module_obj_ack(module);
    if (!obj_ack) {
        return ;
    }
    json_object_set_int(obj_ack, ack);
}

static bool _check_module_ack(struct json_object *module)
{
    int32_t ack = 0;
    struct  json_object *obj_ack = _get_module_obj_ack(module);
    if (!obj_ack) { return false; }
    if (ACK_INIT != (ack = json_object_get_int(obj_ack))) { 
        return false; 
    }

    return true;
}

static const uint8_t CMD_INUSE[] = {
    GET_CMD,
    SET_CMD,
    HEART_CMD,
    END_CMD,
};

static bool _get_module_cmd(struct json_object *module, uint8_t *cmd)
{
    struct  json_object *obj_cmd = NULL;
    if (!(obj_cmd = json_object_object_get(module, STR_MODULE_CMD))) {
        return false;
    }
    *cmd = json_object_get_int(obj_cmd);
    return true;
}

static bool _check_module_cmd(struct json_object *module)
{
    uint8_t cmd = 0;
    if (!_get_module_cmd(module, &cmd)) { return false; }
    for (size_t i = 0; i < sizeof(CMD_INUSE)/sizeof(CMD_INUSE[0]); i++) {
        if (cmd == CMD_INUSE[i]) { return true; }
    }
    return false;
}

static bool _get_module_name(struct json_object *module, uint8_t *name)
{
    struct  json_object *obj_name = NULL;
    char *str = NULL;
    if (!(obj_name = json_object_object_get(module, STR_MODULE_NAME))) {
        return false;
    }

    if (!(str = (char *)json_object_get_string(obj_name))) {
        return false;
    }
    memcpy(name, str, strlen(str));
    return true;
}

static bool _get_module_id(struct json_object *module, uint16_t *id)
{
    struct  json_object *obj_id = NULL;
    if (!(obj_id = json_object_object_get(module, STR_MODULE_ID))) {
        return false;
    }
    *id = json_object_get_int(obj_id);
    return true;
}

static class_module *_get_module(uint16_t id, uint8_t *name)
{
    class_module *_module = get_module_by_id(id);
    if (!_module) { return NULL; }
    if (strncmp((char *)name, _module->section, strlen(_module->section))) {
        return NULL;
    }
    return _module;
}

void reply_pack(struct json_object *packet)
{
    uint8_t ip[4];
    uint16_t port;
    get_addr_info(packet, ip, &port);
    json_object_object_del(packet, STR_ADDRESS);
    send_udp_packet(packet, ip, port);
}

bool unpack_json_module(struct json_object *packet)
{
    int32_t len = 0;
    uint16_t mo_id = 0;
    uint8_t mo_name[127] = { [0 ... 126] = '\0'};
    class_module *_module;
    struct json_object *module = json_object_object_get(packet, STR_MODULE);

    /* ack检查 */
    if (!_check_module_ack(module)) {
        _set_module_ack(module, ACK_ERR);
        reply_pack(packet);
        return false;
    }
    /* cmd检查 */
    if (!_check_module_cmd(module)) {
        _set_module_ack(module, ACK_NOT_SUPPORT_CMD);
        reply_pack(packet);
        return false;
    }

    /* 模块处理 */
    if (!_get_module_id(module, &mo_id) ||
        !_get_module_name(module, mo_name)) {
        _set_module_ack(module, ACK_NO_SUCH_MODULE);
        reply_pack(packet);
        return false;
    }
    if (!(_module = _get_module(mo_id, mo_name))) {
        _set_module_ack(module, ACK_NO_SUCH_MODULE);
        reply_pack(packet);
        return false;
    }
    /* 区分模块 */
    /* 参量处理 */
    if (!(len = _get_key_len(module))) {
        _set_module_ack(module, ACK_KEY_LEN_ERR);
        reply_pack(packet);
        return false;
    }

    _set_module_ack(module, get_set_para_key(_module, packet, len));
    reply_pack(packet);

    return true;
}
