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
 *      "key-ack": ,
 *      "key-context":
 * },
 * "key-end":{
 *      "key": "end"
 * }
 *
 * 
 * */

struct json_object *pack_json(class_module *module)
{
    struct json_object *packet = pack_json_head();

    pack_json_module(packet, module);

    return packet;
}

bool unpack_json(struct json_object *packet)
{
    if (!unpack_json_head(packet)) { return false; }
    return unpack_json_module(packet);
}
