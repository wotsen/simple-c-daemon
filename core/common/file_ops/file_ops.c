/*
 * =====================================================================================
 *
 *       Filename:  file_ops.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/05/2018 09:57:05 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include "../../module/def.h"
#include "file_ops.h"
#include "def_files.h"
#include "../zlog_service/zlog_service.h"

dictionary *__ini_parse(const char *ini_name)
{
    FILE *ini = NULL;
    dictionary *dict = NULL;

    if(NULL == (ini = fopen(ini_name, "r")))
    {
        dbg_error("can not open : [%s]", ini_name);
        return NULL;
    }
    fclose(ini);

    if(NULL == (dict = iniparser_load(ini_name)))
    {
        dbg_error("can not iniparser_load : [%s]", ini_name);
    }
    return dict;
}

bool create_section(dictionary *dict, const char *section)
{
    iniparser_set(dict, section, NULL);
    return true;
}

bool set_key_value(dictionary *dict, const char *section, const char *key,  const char type, char *val)
{
    char section_key[256];
    char s_val[256];

    switch(type)
    {
        case __bool:
            sprintf(s_val, "%s", (*val ? "true" : "false"));
        case __str:
            sprintf(s_val, "%s", val);
        default:
            return false;
    }
    sprintf(section_key, "%s:%s", section, key);

    if(iniparser_set(dict, section_key, (char *)val) < 0)
    {
        dbg_error("set [%s] error", section_key);
        return false;
    }
    return true;
}
bool get_key_value(dictionary *dict, const char *section, const char *key,  const char type, char *val, int len)
{
    char *s = NULL;
    char section_key[256];
    sprintf(section_key, "%s:%s", section, key);

    if(NULL == (s = (char *)iniparser_getstring(dict, section_key, NULL)))
    {
        dbg_error("get [%s] error", section_key);
        return false;
    }
    strncpy(val, s, len);
    return true;
}
bool __ini_save(const char *ini_name, dictionary *dict)
{
    FILE *ini = NULL;
    if(NULL == (ini = fopen(ini_name, "w+")))
    {
        dbg_error("can not save : [%s]", ini_name);
        return false;
    }
    iniparser_dump_ini(dict, ini);
    fclose(ini);
    return true;
}

static const char *dir_path_table[] = {
    BASE_PATH,
    DOC_PATH,
    ETC_PATH,
    LOG_PATH,
    SYS_CONF_PATH,
    DATABASE_PATH,
    NULL
};

void create_dir(void)
{
    int i = 0;
    char cmd[256];
    for(i = 0; NULL != dir_path_table[i]; i++)
    {
        sprintf(cmd, "mkdir %s -p", dir_path_table[i]);
    }
}

FILE *__open_file(const char *path)
{
    FILE *fd;
    if(NULL == (fd = fopen(path, "r+")))
    {
        fd = fopen(path, "w+");
    }
    return fd;
}

extern void open_para_ini(void);
extern void zlog_config_initial(void);

void file_fd_initial(void)
{
    create_dir();
    zlog_config_initial();
    open_para_ini();
}
