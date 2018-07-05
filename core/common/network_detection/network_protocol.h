//
// Created by funto on 2018/6/26.
//

#ifndef DAEMON_NETWORK_PROTOCOL_H
#define DAEMON_NETWORK_PROTOCOL_H
#include "../../module/tools/tools.h"

#define DAEMON_SERVER_PORT      6000
#define VER_CENTER_PORT         6001
#define APPLICATION_PORT        6002

#define NET_DATA_LEN_MAX        1024

#define LOCAL_SYNC_MODULE       0x0001
#define NET_SYNC_MODULE         0x0002

#define ACK_INIT                0xFF
#define ACK_OK                  0x0
#define ACK_ERR                 0x1

#define CMD_GET                 0x0
#define CMD_SET                 0x1

typedef struct{
#define PACK_HEAD_LEN           17
    int src;
    int dest;
    int len;
    int module;
    char ack;
    char pdu[0];
}PACKED class_pack_head;

typedef struct {
#define SYNC_HEART_ID           0x01
    short id;
    char cmd;
    char position[20];
    char os[10];
    char time[30];
    char desc[20];
}PACKED class_sync_pack;

#endif //DAEMON_NETWORK_PROTOCOL_H
