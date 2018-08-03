/*
 * =====================================================================================
 *
 *       Filename:  system_initial.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/05/2018 09:39:00 AM
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
#include <sys/utsname.h>

#include "../../module/module.h"
#include "../common.h"

extern void para_initial(void);

static struct utsname _os_info;

static struct utsname _uname(void)
{
    memset(&_os_info, 0, sizeof(struct utsname));
    uname(&_os_info);
    return _os_info;
}

char *os_type(void)
{
    return _os_info.sysname;
}

char *hostname(void)
{
    return _os_info.nodename;
}
char *os_release(void)
{
    return _os_info.release;
}
char *os_version(void)
{
    return _os_info.version;
}
char *os_machine(void)
{
    return _os_info.machine;
}


void config_initial(void)
{
    file_fd_initial();
}

void system_initial(void)
{
    _uname();
    config_initial();
    para_initial();
}
