/*
 * =====================================================================================
 *
 *       Filename:  protocol.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/04/2018 04:58:31 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <inttypes.h>
#include <stdbool.h>
#include <json-c/json.h>

#include "../module/def.h"
#include "../module//tools/tools.h"

#define STR_HEAD                "head"
#define STR_HEAD_OS_TYPE        "os_type"
#define STR_HEAD_HOSTNAME       "hostname"
#define STR_HEAD_OS_RELEASE     "os_release"
#define STR_HEAD_OS_VERSION     "os_version"
#define STR_HEAD_OS_MACHINE     "os_machine"
#define STR_HEAD_CUR_TIME       "cur_time"

#define STR_MODULE              "module"
#define STR_MODULE_SRC          "src"
#define STR_MODULE_DEST         "dest"
#define STR_MODULE_NAME         "module-name"
#define STR_MODULE_ID           "module-id"
#define STR_MODULE_LEN          "module-len"
#define STR_MODULE_ACK          "module-ack"
#define STR_MODULE_CMD          "module-cmd"

#define STR_KEY                 "key"
#define STR_KEY_NEXT            "key-"
#define STR_KEY_END             "key-end"
#define STR_KEY_NAME            "key-name"
#define STR_KEY_ID              "key-id"
#define STR_KEY_LEN             "key-len"
#define STR_KEY_TYPE            "key-type"
#define STR_KEY_ACK             "key-ack"
#define STR_KEY_CMD             "key-cmd"
#define STR_KEY_CONTEXT         "key-context"

#define JSON_STR_INI            "none"
#define STR_END                 "end"

/* module-cmd */
#define GET_CMD                 0x01
#define SET_CMD                 0x02
#define HEART_CMD               0x03
#define END_CMD                 0xFF

#define ACK_INIT                0xff
#define ACK_OK                  0x0
#define ACK_ERR                 0x1
#define ACK_NO_SUCH_MODULE      0x2
#define ACK_KEY_LEN_ERR         0x3
#define ACK_NOT_SUPPORT_CMD     0x4
#define ACK_KEY_PARSING_EXPECT  0x5

#define KEY_ACK_INIT            0xff
#define KEY_ACK_OK              0x0
#define KEY_ACK_NO_SUCH_KEY     0x1
#define KEY_ACK_LEN_ERR         0x2
#define KEY_ACK_TYPE_ERR        0x3
#define KEY_ACK_MONITOR_ERR     0x4
#define KEY_ACK_NO_SUCH_CMD     0x5

struct _single_json_key {
    char        *name;
    uint16_t    id;
    uint32_t    len;
    char        type;
    char        ack;
    char        cmd;
    uint8_t     pdu[0];
}__attribute__ ((packed));

typedef struct {
    const char *name;
    const uint16_t id;
}PACKED class_para_head;

typedef struct _class_para{
#define PARA_END    {{NULL, 0xFFFF}, 0, 0xf, 0xFF, NULL, \
                     NULL, NULL, NULL, NULL, 0xFFFF, 0, 0, 0}
   class_para_head id; 
   const uint32_t len;
   const char type;
   const uint8_t permission;
   const char *init_val;
   void *address;
   char *(*getset)(struct _single_json_key *json_key,
                      struct _class_para *para_key,
                      struct json_object *key);
   char *(*check)(struct _single_json_key *json_key,
                      struct _class_para *para_key,
                      struct json_object *key);
   char (*valid)(void);
   uint16_t section;
   int32_t para1;
   int32_t para2;
   int32_t para3;
}PACKED class_para;

class_para *get_para_by_id(class_para *para_tables, class_para_head id);
struct json_object *pack_json_para(class_para *para, char *val);
struct json_object *pack_key_end(struct json_object *packet);


typedef struct {
#define MODULE_END  {NULL, 0xFF, NULL, NULL, NULL}
    const char *section;
    const uint8_t id;
    class_para *para_table;
    char *(*exec)(void);
    void (*def_function)(void);
}PACKED class_module;
class_module *get_module_by_id(uint8_t id);

struct os_base_info {
    const char *key;
    char *(*get)();
};

struct json_object *pack_json(class_module *module);

struct json_object *pack_json_head();
struct json_object *pack_json_module(
                    struct json_object *packet,
                    class_module *module);
struct json_object *pack_json_para(
                    class_para *para,
                    char *val);
uint8_t get_set_para_key(
                    class_module *_module,
                    struct json_object *packet, 
                    int32_t len);
struct json_object *pack_key_end(struct json_object *packet);

bool unpack_json(struct json_object *packet);
bool unpack_json_head(struct json_object *packet);
bool unpack_json_module(struct json_object *packet);
bool unpack_json_key(class_module *_module, struct json_object *key);

#endif
