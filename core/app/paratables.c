/*
 * =====================================================================================
 *
 *       Filename:  paratables.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/04/2018 05:16:59 PM
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

#include "../module/def.h"
#include "protocol.h"
#include "../common/file_ops/file_ops.h"
#include "../common/zlog_service/zlog_service.h"
#include "def_paras.h"

static dictionary *para_ini = NULL;

class_para system_base_para[] = {
    {KEY_OS_TYPE,   20,  __str,     RW, "linux",        NULL,           NULL,       NULL,       default_key_tail},
    PARA_END
};

void open_para_ini(void)
{
    FILE *fd = NULL;
    fd = __open_file(PARATABLE_INI);
    if(NULL == fd)
    {
       dbg_error("can not open : [%s]", PARATABLE_INI); 
       return;
    }
    fclose(fd);

    para_ini = __ini_parse(PARATABLE_INI);
    __ini_save(PARATABLE_INI, para_ini);
    iniparser_freedict(para_ini);
}

void para_initial(void)
{
}
