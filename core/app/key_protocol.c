/*
 * =====================================================================================
 *
 *       Filename:  key_protocol.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/02/2018 03:05:45 PM
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

static uint8_t _back[512] = { [0 ... 511] = 0 };

static void _set_key_ack(struct json_object *key, const uint8_t ack)
{
    json_object_set_int(json_object_object_get(key, STR_KEY_ACK), ack);
}

static void _back_para_addr(int32_t len, uint8_t *addr)
{
    memset(_back, 0, sizeof(_back));
    if (addr) {
        memcpy(_back, addr, len);
    }
}

static void _addr_para_back(int32_t len, uint8_t *addr)
{
    if (addr) {
        memcpy(addr, _back, len);
    }
}

static bool _set_json_context_by_type(struct json_object* key, class_para *para_key)
{
    uint32_t len  = para_key->len;
    char     type = para_key->type;
    char s[128] = { [0 ... 127] = 0 };

    json_object_set_int(json_object_object_get(key, STR_KEY_LEN), len);
    switch (type) {
        case __bool:
            json_object_set_string(
                    json_object_object_get(key, STR_KEY_CONTEXT),
                    *(char *)para_key->address ? "true" : "false");
            break;
        case __schar:
            json_object_set_int(
                    json_object_object_get(key, STR_KEY_CONTEXT),
                    *(int8_t *)para_key->address);
            break;
        case __uchar:
            json_object_set_int(
                    json_object_object_get(key, STR_KEY_CONTEXT),
                    *(uint8_t *)para_key->address);
            break;
        case __short:
            json_object_set_int(
                    json_object_object_get(key, STR_KEY_CONTEXT),
                    *(int16_t *)para_key->address);
            break;
        case __ushort:
            json_object_set_int(
                    json_object_object_get(key, STR_KEY_CONTEXT),
                    *(uint16_t *)para_key->address);
            break;
        case __int:
            json_object_set_int(
                    json_object_object_get(key, STR_KEY_CONTEXT),
                    *(int32_t *)para_key->address);
            break;
        case __uint:
            json_object_set_int(
                    json_object_object_get(key, STR_KEY_CONTEXT),
                    *(uint32_t *)para_key->address);
            break;
        case __long:
            json_object_set_int64(
                    json_object_object_get(key, STR_KEY_CONTEXT),
                    *(long *)para_key->address);
            break;
        case __ulong:
            json_object_set_int64(
                    json_object_object_get(key, STR_KEY_CONTEXT),
                    *(unsigned long *)para_key->address);
            break;
        case __llong:
            json_object_set_int64(
                    json_object_object_get(key, STR_KEY_CONTEXT),
                    *(long long *)para_key->address);
            break;
        case __ullong:
            json_object_set_int64(
                    json_object_object_get(key, STR_KEY_CONTEXT),
                    *(unsigned long long *)para_key->address);
            break;
        case __double:
            json_object_set_double(
                    json_object_object_get(key, STR_KEY_CONTEXT),
                    *(double *)para_key->address);
            break;
        case __str:
            json_object_set_string(
                    json_object_object_get(key, STR_KEY_CONTEXT),
                    (char *)para_key->address);
            break;
        case __void:
            digit_to_ascii(s, (const uint8_t *)para_key->address, len);
            s[len << 1] = 0;
            json_object_set_string(
                    json_object_object_get(key, STR_KEY_CONTEXT),
                    s);
            break;
        default:
            dbg_error("data type error");
            _set_key_ack(key, KEY_ACK_TYPE_ERR);
            return false;
    }
    return true;
}


static bool _get_json_context_by_type(struct json_object* key, uint8_t* pdu)
{
    uint32_t len  = (uint32_t)json_object_get_int(
                            json_object_object_get(key, STR_KEY_LEN));
    char type     = (char)json_object_get_int(
                            json_object_object_get(key, STR_KEY_TYPE));
    long long ll_tmp = 0;
    char *s = NULL;
    double ld_tmp = 0.0;
    if (!len) { return false; }
    switch (type) {
        case __bool:
            pdu[0] = strncmp("true", 
                     json_object_get_string(
                            json_object_object_get(key, STR_KEY_CONTEXT)),
                     strlen("true")) ? false : true;
            break;
        case __schar:
            pdu[0] = (int8_t)json_object_get_int(
                     json_object_object_get(key, STR_KEY_CONTEXT));
            break;
        case __uchar:
            pdu[0] = (uint8_t)json_object_get_int(
                     json_object_object_get(key, STR_KEY_CONTEXT));
            break;
        case __short:
            ll_tmp = json_object_get_int(
                        json_object_object_get(key, STR_KEY_CONTEXT));
            memcpy((int16_t *)pdu, (int16_t *)&ll_tmp, sizeof(int16_t));
            break;
        case __ushort:
            ll_tmp = json_object_get_int(
                        json_object_object_get(key, STR_KEY_CONTEXT));
            memcpy((uint16_t *)pdu, (uint16_t *)&ll_tmp, sizeof(uint16_t));
            break;
        case __int:
            ll_tmp = json_object_get_int(
                        json_object_object_get(key, STR_KEY_CONTEXT));
            memcpy((int32_t *)pdu, (int32_t *)&ll_tmp, sizeof(int32_t));
            break;
        case __uint:
            ll_tmp = json_object_get_int(
                        json_object_object_get(key, STR_KEY_CONTEXT));
            memcpy((uint32_t *)pdu, (uint32_t *)&ll_tmp, sizeof(uint32_t));
            break;
        case __long:
            ll_tmp = json_object_get_int64(
                        json_object_object_get(key, STR_KEY_CONTEXT));
            memcpy((long *)pdu, (long *)&ll_tmp, sizeof(long));
            break;
        case __ulong:
            ll_tmp = json_object_get_int64(
                        json_object_object_get(key, STR_KEY_CONTEXT));
            memcpy((unsigned long *)pdu,
                   (unsigned long *)&ll_tmp,
                    sizeof(unsigned long));
            break;
        case __llong:
            ll_tmp = json_object_get_int64(
                        json_object_object_get(key, STR_KEY_CONTEXT));
            memcpy((long long*)pdu, (long long*)&ll_tmp, sizeof(long long));
            break;
        case __ullong:
            ll_tmp = json_object_get_int64(
                        json_object_object_get(key, STR_KEY_CONTEXT));
            memcpy((unsigned long long *)pdu,
                   (unsigned long long *)&ll_tmp,
                    sizeof(unsigned long long));
            break;
        case __double:
            ld_tmp = json_object_get_double(
                         json_object_object_get(key, STR_KEY_CONTEXT));
            memcpy((double*)pdu, &ld_tmp, sizeof(double));
            break;
        case __str:
            memcpy(pdu,
                   json_object_get_string(
                         json_object_object_get(key, STR_KEY_CONTEXT)),
                   len);
            break;
        case __void:
            s = (char *)json_object_get_string(
                         json_object_object_get(key, STR_KEY_CONTEXT));
            ll_tmp = strlen(s);
            if (len * 2 < ll_tmp) {
                ll_tmp = len * 2;
            }
            ascii_to_hex((uint8_t *)pdu, s, (uint32_t)ll_tmp);
            break;
        default:
            dbg_error("data type error");
            _set_key_ack(key, KEY_ACK_TYPE_ERR);
            return false;
            break;
    }
    return true;
}

static bool _trans_cmd(struct _single_json_key *json_key,
                       class_para *para_key,
                       struct json_object *key)
{
    switch (json_key->cmd) {
        case SET_CMD:
            if (para_key->address) {
                memcpy((uint8_t* )para_key->address,
                        json_key->pdu,
                        para_key->len);
            }
            break;
        case GET_CMD:
            if (para_key->address) {
                if (!_set_json_context_by_type(key, para_key)) {
                    return false;
                }
            }
            break;
        case HEART_CMD:
            dbg_error("%s", json_key->pdu);
            break;
        default:
            _set_key_ack(key, KEY_ACK_NO_SUCH_CMD);
            return false;
    }
    return true;
}


static bool _key_exec(struct _single_json_key *json_key,
                      class_para *para_key,
                      struct json_object *key)
{
    bool ret = false;
    _back_para_addr(para_key->len, (uint8_t *)para_key->address);
    if (!_trans_cmd(json_key, para_key, key)) {
        return false;
    }

    if (para_key->check) {
        if (!para_key->check(json_key, para_key, key)) {
            if (para_key->getset) {
                ret = para_key->getset(json_key, para_key, key);
            }
        } else {
            ret = false;
        }
    }

    if (!ret) {
        _addr_para_back(para_key->len, (uint8_t *)para_key->address);
    } else {
        _set_key_ack(key, KEY_ACK_OK);
        ret = true;
    }
    return ret;
}

static struct _single_json_key *_analysis_json_key(struct json_object *key)
{
    uint32_t len  = (uint32_t)json_object_get_int(
                            json_object_object_get(key, STR_KEY_LEN));

    struct _single_json_key *_json_key = 
                            (struct _single_json_key *)
                                memory_alloc(sizeof(struct _single_json_key)+len);
    _json_key->name = (char *)json_object_get_string(
                            json_object_object_get(key, STR_KEY_NAME));
    _json_key->id   = (uint16_t)json_object_get_int(
                            json_object_object_get(key, STR_KEY_ID));
    _json_key->len  = (uint32_t)json_object_get_int(
                            json_object_object_get(key, STR_KEY_LEN));
    _json_key->type = (char)json_object_get_int(
                            json_object_object_get(key, STR_KEY_TYPE));
    _json_key->ack  = (char)json_object_get_int(
                            json_object_object_get(key, STR_KEY_ACK));
    _json_key->cmd  = (char)json_object_get_int(
                            json_object_object_get(key, STR_KEY_CMD));
    if (!_get_json_context_by_type(key, _json_key->pdu)) {
        free(_json_key);
        return NULL;
    }
    return _json_key;
}

static bool _check_key_valid(struct json_object *key)
{
    if (!json_object_object_get(key, STR_KEY_NAME) ||
        !json_object_object_get(key, STR_KEY_ID) ||
        !json_object_object_get(key, STR_KEY_LEN) ||
        !json_object_object_get(key, STR_KEY_TYPE) ||
        !json_object_object_get(key, STR_KEY_ACK) ||
        !json_object_object_get(key, STR_KEY_CMD) ||
        !json_object_object_get(key, STR_KEY_CONTEXT)) {
        return false;
    }
    return true;
}


bool unpack_json_key(class_module *_module, struct json_object *key)
{
    bool ret = true;
    class_para *_para_table = _module->para_table;
    class_para *use_key     = NULL;
    struct _single_json_key *_json_key = _analysis_json_key(key);
    if (!_json_key) { return false; }

    for (int i = 0; NULL != _para_table[i].id.name; i++) {
        if (_para_table[i].id.id == _json_key->id) {
            use_key = _para_table;
            break;
        }
    }
    if (!use_key) {
        free(_json_key);
        _set_key_ack(key, KEY_ACK_NO_SUCH_KEY);
        return false;
    }
    ret = _key_exec(_json_key, use_key, key);
    free(_json_key);
    return ret;
}

uint8_t get_set_para_key(
        class_module *_module,
        struct json_object *packet, 
        int32_t len)
{
    if (!_module->para_table) { return 0; }

    int8_t ret  = 0;
    bool   check_key = true;
    int32_t i   = 0;
    char    key_name[125];
    struct  json_object *key     = NULL;
    do {
        i++;
        sprintf(key_name, "%s%d", STR_KEY_NEXT, i);
        if (!(key = json_object_object_get(packet, (const char *)key_name))) {
            return ACK_KEY_LEN_ERR;
        }
        check_key = _check_key_valid(key);
        ret |= check_key ? 0 : 1;
        if (!check_key) { continue; }
        ret |= unpack_json_key(_module, key) ? 0 : 1;
    } while (i <= len);

    return ret ? ACK_KEY_PARSING_EXPECT : ACK_OK;
}

struct json_object *pack_key_end(struct json_object *packet)
{
    struct json_object *key_end = json_object_new_object();

    json_object_object_add(key_end, STR_KEY, json_object_new_string(STR_END));
    json_object_object_add(packet, STR_KEY_END, key_end);

    return packet;
}

struct json_object *pack_json_para(class_para *para, char *val)
{
    struct json_object *key = json_object_new_object();
    char   str[256];

    json_object_object_add(key, STR_KEY_NAME, 
                           json_object_new_string(para->id.name));
    json_object_object_add(key, STR_KEY_ID, 
                           json_object_new_int(para->id.id));
    json_object_object_add(key, STR_KEY_LEN, 
                           json_object_new_int(para->len));
    json_object_object_add(key, STR_KEY_TYPE, 
                           json_object_new_int(para->type));
    json_object_object_add(key, STR_KEY_ACK, 
                           json_object_new_int(KEY_ACK_INIT));
    json_object_object_add(key, STR_KEY_CMD, 
                           json_object_new_int(HEART_CMD));
    
    if (!para->len) { return key; }

    switch (para->type) {
        case __bool:
            json_object_object_add(
                        key, 
                        STR_KEY_CONTEXT,
                        json_object_new_string(*val ? "true" : "false"));
            break;
        case __schar:
            json_object_object_add(
                        key,
                        STR_KEY_CONTEXT, 
                        json_object_new_int(*val));
            break;
        case __uchar:
            json_object_object_add(
                        key,
                        STR_KEY_CONTEXT, 
                        json_object_new_int(*((uint8_t*)val)));
            break;
        case __short:
            json_object_object_add(
                        key,
                        STR_KEY_CONTEXT, 
                        json_object_new_int(*((int16_t*)val)));
            break;
        case __ushort:
            json_object_object_add(
                        key,
                        STR_KEY_CONTEXT, 
                        json_object_new_int(*((uint16_t*)val)));
            break;
        case __int:
            json_object_object_add(
                        key,
                        STR_KEY_CONTEXT, 
                        json_object_new_int(*((int32_t*)val)));
            break;
        case __uint:
            json_object_object_add(
                        key,
                        STR_KEY_CONTEXT, 
                        json_object_new_int(*((uint32_t*)val)));
            break;
        case __long:
            json_object_object_add(
                        key,
                        STR_KEY_CONTEXT, 
                        json_object_new_int64(*((long*)val)));
            break;
        case __ulong:
            json_object_object_add(
                        key,
                        STR_KEY_CONTEXT, 
                        json_object_new_int64(*((unsigned long*)val)));
            break;
        case __llong:
            json_object_object_add(
                        key,
                        STR_KEY_CONTEXT, 
                        json_object_new_int64(*((long long*)val)));
            break;
        case __ullong:
            json_object_object_add(
                        key,
                        STR_KEY_CONTEXT, 
                        json_object_new_int64(*((unsigned long long*)val)));
            break;
        case __double:
            json_object_object_add(
                        key,
                        STR_KEY_CONTEXT, 
                        json_object_new_double(*((double*)val)));
            break;
        case __str:
            sprintf(str, "%s", val);
            json_object_object_add(
                        key,
                        STR_KEY_CONTEXT, 
                        json_object_new_string(str));
            break;
        case __void:
            digit_to_ascii(str, (const uint8_t *)val, para->len);
            str[para->len << 1] = 0;
            json_object_object_add(
                        key,
                        STR_KEY_CONTEXT, 
                        json_object_new_string(str));
            break;
        default:
            dbg_error("data type error");
            json_object_put(key);
            key = NULL;
            break;
    }

    return key;
}
