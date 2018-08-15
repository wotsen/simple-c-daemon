/*
 * =====================================================================================
 *
 *       Filename:  network_udp_list.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/01/2018 03:16:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __NETWORK_LIST__
#define __NETWORK_LIST__

#include <json-c/json.h>
#include "../../module/list.h"

#define STR_ADDRESS         "address"
#define STR_IP              "ip"
#define STR_PORT            "port"

void push_udp_data_list(struct json_object *recv);
struct json_object *pop_udp_data_list(void);

#endif
