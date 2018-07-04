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

static struct utsname os_info;

static struct utsname __uname(void)
{
    memset(&os_info, 0, sizeof(struct utsname));
    uname(&os_info);
    return os_info;
}

char *os_type(void)
{
    return os_info.sysname;
}

char *hostname(void)
{
    return os_info.nodename;
}
char *os_release(void)
{
    return os_info.release;
}
char *os_version(void)
{
    return os_info.version;
}
char *os_machine(void)
{
    return os_info.machine;
}

void system_start(void)
{
    __uname();
    network_start();
    while(1)
    {
        m_ostime_delay(OS_SEC(10));
    }
}
