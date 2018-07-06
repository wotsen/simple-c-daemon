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

bool check_section(dictionary *dict, const char *section)
{
    return iniparser_find_entry(dict, section) ? true : false;
}

bool initial_key_value(dictionary *dict, const char *section, const char *key, char *val)
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

bool set_key_value(dictionary *dict, const char *section, const char *key,  const char type, char *val)
{
    char section_key[256];
    char s_val[256];
    short s_tmp = 0;
    int i_tmp = 0;
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
            sprintf(s_val, "%d", (unsigned char)*val);
            break;
        case __short:
            memcpy(&s_tmp, val, sizeof(s_tmp));
            sprintf(s_val, "%d", s_tmp);
            break;
        case __ushort:
            memcpy(&s_tmp, val, sizeof(s_tmp));
            sprintf(s_val, "%d", (unsigned short)s_tmp);
            break;
        case __int:
            memcpy(&i_tmp, val, sizeof(i_tmp));
            sprintf(s_val, "%d", i_tmp);
            break;
        case __uint:
            memcpy(&i_tmp, val, sizeof(i_tmp));
            sprintf(s_val, "%u", (unsigned int)i_tmp);
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

#define dbg 1

bool strto_type_val(const char *s, char *val, const char type, int len)
{
    long long ll_tmp = 0;
    double d_tmp = 0.0;
    switch(type)
    {
        case __bool:
            *val = strcmp(s, "true") ? false : true;
#if dbg
            dbg_print("__bool : %s", *val);
#endif
            break;
        case __char:
            ll_tmp = strtoll(s, NULL, 0);
            if(check_strtoll(ll_tmp))
            {
                *val = (char)ll_tmp;
            }
#if dbg
            dbg_print("source data : %lld", ll_tmp);
            dbg_print("__char : %d", *val);
#endif
            break;
        case __uchar:
            ll_tmp = strtoll(s, NULL, 0);
            if(check_strtoll(ll_tmp))
            {
                memcpy((unsigned char *)val, (unsigned char *)&ll_tmp, sizeof(unsigned char));
            }
#if dbg
            dbg_print("source data : %lld", ll_tmp);
            dbg_print("__uchar : %d", (unsigned char)*val);
#endif
            break;
        case __short:
            ll_tmp = strtoll(s, NULL, 0);
            if(check_strtoll(ll_tmp))
            {
                memcpy((short *)val, (short *)&ll_tmp, sizeof(short));
            }
#if dbg
            dbg_print("source data : %lld", ll_tmp);
            dbg_print("__short : %d", (short)*val);
#endif
            break;
        case __ushort:
            ll_tmp = strtoll(s, NULL, 0);
            if(check_strtoll(ll_tmp))
            {
                memcpy((unsigned short *)val, (unsigned short *)&ll_tmp, sizeof(unsigned short));
            }
#if dbg
            dbg_print("source data : %lld", ll_tmp);
            dbg_print("__ushort : %d", (unsigned short)*val);
#endif
            break;
        case __int:
            ll_tmp = strtoll(s, NULL, 0);
            if(check_strtoll(ll_tmp))
            {
                memcpy((int *)val, (int *)&ll_tmp, sizeof(int));
            }
#if dbg
            dbg_print("source data : %lld", ll_tmp);
            dbg_print("__int : %d", (int)*val);
#endif
            break;
        case __uint:
            ll_tmp = strtoll(s, NULL, 0);
            if(check_strtoll(ll_tmp))
            {
                memcpy((unsigned int *)val, (unsigned int *)&ll_tmp, sizeof(unsigned int));
            }
#if dbg
            dbg_print("source data : %lld", ll_tmp);
            dbg_print("__uint : %u", (unsigned int)*val);
#endif
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
                memcpy((unsigned long *)val, (unsigned long *)&ll_tmp, sizeof(unsigned long));
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
                memcpy((unsigned long long *)val, (unsigned long long *)&ll_tmp, sizeof(unsigned long long));
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
#if dbg
            dbg_print("__str : %s", val);
#endif
            break;
        default:
            return false;
    }
    return true;
}
#undef dbg


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
    return strto_type_val((const char *)s, val, type, len);
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
