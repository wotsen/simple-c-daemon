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

char test_base_path[60];
unsigned char test_uint8 = 0;
short test_int16 = 0;
unsigned short test_uint16 = 0;
int test_int32 = 0;
unsigned int test_uint32 = 0;

class_para system_base_para[] = {
    {KEY_OS_TYPE,   20,  __str,     rw,     NULL,            NULL,           NULL,       NULL,       default_key_tail},
    {KEY_CONF_DIR,  60,  __str,     w_,     BASE_PATH,       test_base_path,           NULL,       NULL,       default_key_tail},
    {{"test-uint8", 0},  1,  __uchar,     w_,     "0xff",  (char *)&test_uint8,           NULL,       NULL,       default_key_tail},
    {{"test-int16", 0},  2,  __short,     w_,     "-55", (char *)&test_int16,           NULL,       NULL,       default_key_tail},
    {{"test-uint16", 0},  2,  __ushort,     w_,   "0xffff", (char *)&test_uint16,           NULL,       NULL,       default_key_tail},
    {{"test-int32", 0},  4,  __int,     w_,     "-65538",       (char *)&test_int32,           NULL,       NULL,       default_key_tail},
    {{"test-uint32", 0},  4,  __uint,     w_,     "0xffffffff",       (char *)&test_uint32,           NULL,       NULL,       default_key_tail},
    PARA_END
};

class_module __modules[] = {
    {SEC_SYSTEM_BASE,     ID_SYSTEM_BASE,    system_base_para,   NULL,   NULL},
    MODULE_END
};

bool check_para_key(const char *section, const char *key)
{
    char buf[256];
    sprintf(buf, "%s:%s", section, key);
    return check_section(para_ini, buf);
}

bool check_module_section(const char *section)
{
    return check_section(para_ini, section);
}
bool create_module_section(const char *section)
{
    return create_section(para_ini, section);
}

bool ini_para_key(const char *section, const char *key, char *val)
{
    return initial_key_value(para_ini, section, key, val);
}
bool set_para_key(const char *section, const char *key, const char type, char *val)
{
    return set_key_value(para_ini, section, key, type, val);
}
bool get_para_key(const char *section, const char *key, const char type, char *val, int len)
{
    return get_key_value(para_ini, section, key, type, val, len);
}

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
//    __ini_save(PARATABLE_INI, para_ini);
//    iniparser_freedict(para_ini);
}

void para_initial(void)
{
    int i = 0;
    int j = 0;
    for(i = 0; NULL != __modules[i].section; i++)
    {
        if(!check_module_section(__modules[i].section)){
            create_module_section(__modules[i].section);
        }
        for(j = 0; NULL != __modules[i].para_table[j].id.name; j++)
        {
            if(NULL != __modules[i].para_table[j].init_val){
                if(!check_para_key(__modules[i].section, __modules[i].para_table[j].id.name)){
                    ini_para_key(__modules[i].section, __modules[i].para_table[j].id.name, \
                            (char *)__modules[i].para_table[j].init_val);
                    if(NULL != __modules[i].para_table[j].address){
                        strto_type_val((const char *)__modules[i].para_table[j].init_val, \
                                (char *)__modules[i].para_table[j].address, \
                                (const char)__modules[i].para_table[j].type, __modules[i].para_table[j].len);
                    }
                }
                if(NULL != __modules[i].para_table[j].address){
                    get_para_key(__modules[i].section, __modules[i].para_table[j].id.name, \
                            (const char)__modules[i].para_table[j].type, (char *)__modules[i].para_table[j].address,\
                            __modules[i].para_table[j].len);
                }
            }
        }
    }
    dbg_print("val : %d", test_uint8);
    dbg_print("val : %d", test_int16);
    dbg_print("val : %d", test_uint16);
    dbg_print("val : %d", test_int32);
    dbg_print("val : %u", test_uint32);
    __ini_save(PARATABLE_INI, para_ini);
}
