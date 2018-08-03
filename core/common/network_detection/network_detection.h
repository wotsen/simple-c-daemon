/******************************************    *******************************

      > File Name: network_detection.h

      > Author: Ywl

      > Descripsion:

      > Created Time:     Mon 07 May 2018 09:55:52 PM CST

      > Modify Time: 

 *********************************    ***************************************/

#ifndef _NETWORK_DETECTION_H
#define _NETWORK_DETECTION_H
#include <json-c/json.h>
#include <stdbool.h>
#include "network_list.h"

#define DAEMON_SERVER_PORT      6000
#define VER_CENTER_PORT         6001
#define APPLICATION_PORT        6002

#define DAEMON_SSL_PORT         7000
#define APPLICATION_SSL_PORT    7002

#define NET_DATA_LEN_MAX        1024

typedef struct json_object *(*udp_task_function)(void);

bool put_udp_task(udp_task_function fun);
void udp_net_initial(void);
void *udp_network_task(void*);

#endif
