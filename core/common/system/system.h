/******************************************    *******************************

      > File Name: system.h

      > Author: Ywl

      > Descripsion:

      > Created Time:     Tue 08 May 2018 02:29:05 AM PDT

      > Modify Time: 

 *********************************    ***************************************/

#ifndef _SYSTEM_H
#define _SYSTEM_H

char *os_type(void);
char *hostname(void);
char *os_release(void);
char *os_version(void);
char *os_machine(void);

void system_start(void);

#endif
