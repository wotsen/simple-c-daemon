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


/* module-cmd */
#define GET_CMD             0x01
#define SET_CMD             0x02
#define HEART_CMD           0x03
#define END_CMD             0xFF

#define ACK_INIT            0xFF
#define ACK_OK              0x0
#define ACK_ERR             0x1

typedef struct {
    const char *name;
    const uint16_t id;
}PACKED class_para_head;

typedef struct {
#define PARA_END    {{NULL, 0xFFFF}, 0, 0xf, 0xFF, NULL, \
                     NULL, NULL, NULL, NULL, 0xFFFF, 0, 0, 0}
   class_para_head id; 
   const uint32_t len;
   const char type;
   const uint8_t permission;
   const char *init_val;
   void *address;
   char *(*getset)(void);
   char *(*check)(void);
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

struct json_object *packet_json(class_module *module);
bool unpack_json_head(struct json_object *packet);
bool unpack_json_module(struct json_object *packet, 
                        struct json_object *module);
bool unpack_json_key(struct json_object *packet,
                     struct json_object *module,
                     struct json_object *key);

#endif
