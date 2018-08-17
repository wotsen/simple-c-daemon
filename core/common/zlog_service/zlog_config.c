/*
 * =====================================================================================
 *
 *       Filename:  zlog_config.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/05/2018 03:03:42 PM
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

#include "zlog_service.h"
#include "zlog_config.h"

char zlog_config_path[60] = SYSTEM_LOG_CONF;

void zlog_config_initial(void)
{
    FILE *fd;
    fd = fopen(zlog_config_path, "w");
    fprintf(fd, zlog_config, LOG_PATH, LOG_PATH, LOG_PATH, LOG_PATH); 
    fflush(fd);
    fclose(fd);
}
