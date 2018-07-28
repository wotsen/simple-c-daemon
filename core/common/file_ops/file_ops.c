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
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>

#include "../../module/def.h"
#include "file_ops.h"
#include "def_files.h"
#include "../zlog_service/zlog_service.h"

dictionary *ini_parse(const char *ini_name)
{
    FILE *ini = NULL;
    dictionary *dict = NULL;

    if(!(ini = fopen(ini_name, "r")))
    {
        dbg_error("can not open : [%s]", ini_name);
        return NULL;
    }
    fclose(ini);

    if(!(dict = iniparser_load(ini_name)))
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

bool check_section(dictionary *dict, const char *section)
{
    return iniparser_find_entry(dict, section) ? true : false;
}

bool initial_key_value(dictionary *dict, const char *section, 
                       const char *key, char *val)
{
    char section_key[256];
    sprintf(section_key, "%s:%s", section, key);

    if(iniparser_set(dict, section_key, (char *)val) < 0)
    {
        dbg_error("set [%s] error", section_key);
        return false;
    }

    return true;
}

bool set_key_value(dictionary *dict, const char *section,
                   const char *key,  const char type, char *val)
{
    char section_key[256];
    char s_val[256];
    int16_t s_tmp = 0;
    int32_t i_tmp = 0;
    long l_tmp = 0;
    long long ll_tmp = 0;
    double d_tmp = 0.0;

    switch(type)
    {
        case __bool:
            sprintf(s_val, "%s", (*val ? "true" : "false"));
            break;
        case __char:
            sprintf(s_val, "%d", *val);
            break;
        case __uchar:
            sprintf(s_val, "%d", (uint8_t)*val);
            break;
        case __short:
            memcpy(&s_tmp, val, sizeof(s_tmp));
            sprintf(s_val, "%d", s_tmp);
            break;
        case __ushort:
            memcpy(&s_tmp, val, sizeof(s_tmp));
            sprintf(s_val, "%d", (uint16_t)s_tmp);
            break;
        case __int:
            memcpy(&i_tmp, val, sizeof(i_tmp));
            sprintf(s_val, "%d", i_tmp);
            break;
        case __uint:
            memcpy(&i_tmp, val, sizeof(i_tmp));
            sprintf(s_val, "%u", (uint32_t)i_tmp);
            break;
        case __long:
            memcpy(&l_tmp, val, sizeof(l_tmp));
            sprintf(s_val, "%ld", l_tmp);
            break;
        case __ulong:
            memcpy(&l_tmp, val, sizeof(l_tmp));
            sprintf(s_val, "%lu", (unsigned long)l_tmp);
            break;
        case __llong:
            memcpy(&ll_tmp, val, sizeof(ll_tmp));
            sprintf(s_val, "%lld", ll_tmp);
            break;
        case __ullong:
            memcpy(&ll_tmp, val, sizeof(ll_tmp));
            sprintf(s_val, "%llu", (unsigned long long)ll_tmp);
            break;
        case __double:
            memcpy(&d_tmp, val, sizeof(d_tmp));
            sprintf(s_val, "%f", d_tmp);
            break;
        case __str:
            sprintf(s_val, "%s", val);
            break;
        default:
            return false;
    }
    sprintf(section_key, "%s:%s", section, key);

    if(iniparser_set(dict, section_key, (char *)s_val) < 0)
    {
        dbg_error("set [%s] error", section_key);
        return false;
    }

    return true;
}

bool check_strtoll(long long val)
{
    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
            || (errno != 0 && val == 0)) {
        dbg_error("trans error");
        return false;
    }

    return true;
}
bool check_strtod(double val)
{
    if ((errno == ERANGE && (val == HUGE_VALF || val == HUGE_VALL))
            || (errno != 0 && val == 0.0)) {
        dbg_error("trans error");
        return false;
    }

    return true;
}



bool strto_type_val(const char *s, char *val, const char type, int32_t len)
{
    long long ll_tmp = 0;
    double d_tmp = 0.0;
    switch(type)
    {
        case __bool:
            *val = strcmp(s, "true") ? false : true;
            break;
        case __char:
            ll_tmp = strtoll(s, NULL, 0);
            if(check_strtoll(ll_tmp))
            {
                *val = (char)ll_tmp;
            }
            break;
        case __uchar:
            ll_tmp = strtoll(s, NULL, 0);
            if(check_strtoll(ll_tmp))
            {
                memcpy((uint8_t *)val, (uint8_t *)&ll_tmp, sizeof(uint8_t));
            }
            break;
        case __short:
            ll_tmp = strtoll(s, NULL, 0);
            if(check_strtoll(ll_tmp))
            {
                memcpy((int16_t *)val, (int16_t *)&ll_tmp, sizeof(int16_t));
            }
            break;
        case __ushort:
            ll_tmp = strtoll(s, NULL, 0);
            if(check_strtoll(ll_tmp))
            {
                memcpy((uint16_t *)val, (uint16_t *)&ll_tmp, sizeof(uint16_t));
            }
            break;
        case __int:
            ll_tmp = strtoll(s, NULL, 0);
            if(check_strtoll(ll_tmp))
            {
                memcpy((int32_t *)val, (int32_t *)&ll_tmp, sizeof(int32_t));
            }
            break;
        case __uint:
            ll_tmp = strtoll(s, NULL, 0);
            if(check_strtoll(ll_tmp))
            {
                memcpy((uint32_t *)val, (uint32_t *)&ll_tmp, sizeof(uint32_t));
            }
            break;
        case __long:
            ll_tmp = strtoll(s, NULL, 0);
            if(check_strtoll(ll_tmp))
            {
                memcpy((long *)val, (long *)&ll_tmp, sizeof(long));
            }
            break;
        case __ulong:
            ll_tmp = strtoll(s, NULL, 0);
            if(check_strtoll(ll_tmp))
            {
                memcpy((unsigned long *)val, 
                       (unsigned long *)&ll_tmp, 
                        sizeof(unsigned long));
            }
            break;
        case __llong:
            ll_tmp = strtoll(s, NULL, 0);
            if(check_strtoll(ll_tmp))
            {
                memcpy((long long *)val, (long long *)&ll_tmp, sizeof(long long));
            }
            break;
        case __ullong:
            ll_tmp = strtoll(s, NULL, 0);
            if(check_strtoll(ll_tmp))
            {
                memcpy((unsigned long long *)val,
                       (unsigned long long *)&ll_tmp, 
                       sizeof(unsigned long long));
            }
            break;
        case __double:
            d_tmp = strtod(s, NULL);
            if(check_strtod(d_tmp))
            {
                memcpy((double *)val, (double *)&d_tmp, sizeof(double));
            }
            break;
        case __str:
            strncpy(val, s, len);
            break;
        case __void:
            memcpy(val, s, len);
            break;
        default:
            return false;
    }

    return true;
}


bool get_key_value(dictionary *dict, const char *section, 
                   const char *key,  const char type, 
                   char *val, int32_t len)
{
    char *s = NULL;
    char section_key[256];
    sprintf(section_key, "%s:%s", section, key);

    if(!(s = (char *)iniparser_getstring(dict, section_key, NULL)))
    {
        dbg_error("get [%s] error", section_key);
        return false;
    }

    return strto_type_val((const char *)s, val, type, len);
}
bool ini_save(const char *ini_name, dictionary *dict)
{
    FILE *ini = NULL;
    if(!(ini = fopen(ini_name, "w+")))
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
    int32_t i = 0;
    char cmd[256];

    for(i = 0; NULL != dir_path_table[i]; i++)
    {
        sprintf(cmd, "mkdir %s -p", dir_path_table[i]);
    }
}

FILE *open_file(const char *path)
{
    FILE *fd;

    if(!(fd = fopen(path, "r+")))
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
