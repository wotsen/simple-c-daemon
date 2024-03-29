/******************************************    *******************************

      > File Name: system.c

      > Author: Ywl

      > Descripsion:

      > Created Time:     Tue 08 May 2018 02:29:22 AM PDT

      > Modify Time: 

 *********************************    ***************************************/
#include <stdio.h>
#include <sys/utsname.h>

#include "../../module/module.h"
#include "../common.h"

extern void system_initial(void);
extern void network_start(void);

void system_start(void)
{
    system_initial();
    system_info("\n..............system start....................");
    network_start();
    while (1) {
        ostime_delay(OS_SEC(10));
    }
}
