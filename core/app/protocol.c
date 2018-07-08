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

#include "protocol.h"

/*
 * 数据包格式:
 * "head":{
 *      "os-type": ,
 *      "hostnme": ,
 *      "os-release": ,
 *      "os-version": ,
 *      "os-machine": 
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
 *      "key-cmd": ,
 *      "key-type": ,
 *      "key-len": ,
 *      "key-context":
 * },
 * "key-end":{
 *      "key": "end"
 * }
 *
 * 
 * */

bool unpack_json_head(struct json_object *packet)
{
    struct json_object *head = json_object_object_get(packet, "head");
    struct json_object *module = json_object_object_get(packet, "module");
    if((NULL == head) || (NULL == module))
    {
        return false;
    }
    return unpack_json_module(packet, module);
}

bool unpack_json_module(struct json_object *packet, struct json_object *module)
{
    struct json_object *key = NULL;
    struct json_object *key_len = NULL;
    char key_name[125];
    int len = 0;
    int i = 1;
    bool ret = true;

    if(NULL == (key_len = json_object_object_get(module, "len")))
    {
        return false;
    }
    if(0 == (len = json_object_get_int(key_len)))
    {
        return false;
    }
    do{
        sprintf(key_name, "key-%d", i);
        if(NULL == (key = json_object_object_get(packet, (const char *)key_name)))
        {
            return false;
        }
        if(!unpack_json_key(packet, module, key))
        {
            ret = false;
        }
        i++;
    }while(i <= len);
    return ret;
}

bool unpack_json_key(struct json_object *packet, struct json_object *module, struct json_object *key)
{
    return true;
}

