/*
 * =====================================================================================
 *
 *       Filename:  head_protocol.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/02/2018 02:57:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "../module/module.h"
#include "../common/common.h"
#include "protocol.h"

struct _os_base_info {
    const char *_type;
    const char *_hostname;
    const char *_release;
    const char *_version;
    const char *_machine;
};

static const struct os_base_info system_uname[] = {
    {STR_HEAD_OS_TYPE,     os_type},
    {STR_HEAD_HOSTNAME,    hostname},
    {STR_HEAD_OS_RELEASE,  os_release},
    {STR_HEAD_OS_VERSION,  os_version},
    {STR_HEAD_OS_MACHINE,  os_machine},
    {NULL, NULL}
};

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
    json_object_object_add(hobj, STR_HEAD_CUR_TIME, json_object_new_string(time));
    json_object_object_add(obj, STR_HEAD, hobj);

    return obj;
}

static bool _record_to_sqlite3_db(
        struct _os_base_info os_head,
        uint8_t *ip,
        uint16_t post)
{
    return true;
}

static bool _record_packet_site_info(struct json_object *head,
                                    struct json_object *addr)
{
    const char *_os_type    = json_object_get_string(
                                json_object_object_get(head, STR_HEAD_OS_TYPE));
    const char *_hostname   = json_object_get_string(
                                json_object_object_get(head, STR_HEAD_HOSTNAME));
    const char *_os_release = json_object_get_string(
                                json_object_object_get(head, STR_HEAD_OS_RELEASE));
    const char *_os_version = json_object_get_string(
                                json_object_object_get(head, STR_HEAD_OS_VERSION));
    const char *_os_machine = json_object_get_string(
                                json_object_object_get(head, STR_HEAD_OS_MACHINE));

    if (!_os_type || !_hostname || !_os_release ||
        !_os_version || !_os_machine) {
        return false;
    }
    struct _os_base_info os_head = {
        ._type      = _os_type,
        ._hostname  = _hostname,
        ._release   = _os_release,
        ._version   = _os_version,
        ._machine   = _os_machine
    };

    uint16_t port = 0;
    uint8_t ip[4] = { [0 ... 3] = 0 };
    get_addr_info_by_addr(addr, ip, &port);

    return _record_to_sqlite3_db(os_head, ip, port);
}

bool unpack_json_head(struct json_object *packet)
{
    struct json_object *head   = json_object_object_get(packet, STR_HEAD);
    struct json_object *module = json_object_object_get(packet, STR_MODULE);
    struct json_object *addr   = json_object_object_get(packet, STR_ADDRESS);

    if (!head || !module || !addr) { return false; }

    /* 检查来源是否记录在案 */
    if (!_record_packet_site_info(head, addr)) { return false; /* 直接丢掉 */ }

    return true;
}
