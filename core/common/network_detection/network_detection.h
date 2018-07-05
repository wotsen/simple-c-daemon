/******************************************    *******************************

      > File Name: network_detection.h

      > Author: Ywl

      > Descripsion:

      > Created Time:     Mon 07 May 2018 09:55:52 PM CST

      > Modify Time: 

 *********************************    ***************************************/

#ifndef _NETWORK_DETECTION_H
#define _NETWORK_DETECTION_H



typedef struct{
    unsigned int length;
    unsigned char cmd;
    char pdu[0];
}PACKED class_daemon;

void network_start(void);

#endif
