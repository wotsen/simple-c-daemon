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
#include "../module//tools/tools.h"

typedef struct {
    const char *name;
    const unsigned short id;
}PACKED class_para_head;

typedef struct {
#define PARA_END    {{NULL, 0xFFFF}, 0, 0xFF, 0xFF, NULL, NULL, NULL, NULL, NULL, 0xFFFF, 0, 0, 0}
   class_para_head id; 
   const unsigned char len;
   const unsigned char type;
   const unsigned char permission;
   const char *init_val;
   void *address;
   char *(*getset)(void);
   char *(*check)(void);
   char (*valid)(void);
   unsigned short section;
   int para1;
   int para2;
   int para3;
}PACKED class_para;


typedef struct {
    const char *section;
    const unsigned char id;
    class_para *para_table;
    char *(*exec)(void);
    void (*def_function)(void);
}PACKED class_module;

#endif
