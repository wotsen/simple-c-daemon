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
#include "def_system_base.h"
#include "def_application.h"
#include "def_network.h"
#include "extern_para.h"

static dictionary *para_ini = NULL;

class_para system_base_para[] = {
    {KEY_OS_TYPE,               20, __str,     r_, NULL,        NULL,
        NULL,   NULL,   default_key_tail},
    PARA_END
};

class_para applications_para[] = {
    {KEY_TX_MYSQL_PASS,         40, __str,     r_, NULL,        NULL,
        NULL,   NULL,   default_key_tail},
    {KEY_COMMON_ACC_PASS,       40, __str,     r_, NULL,        NULL,
        NULL,   NULL,   default_key_tail},

    /* net */
    {KEY_LOCAL_UDP_PORT,        2,  __ushort,  rw, "6000",      &g_local_udp_port,      
        NULL,   NULL,   default_key_tail},
    {KEY_DJANGO_UDP_PORT,       2,  __ushort,  rw, "6002",      &g_application_udp_port,
        NULL,   NULL,   default_key_tail},
    {KEY_LOCAL_SSL_PORT,        2,  __ushort,  rw, "7000",      &g_local_ssl_port,       
        NULL,   NULL,   default_key_tail},
    {KEY_DJANGO_SSL_PORT,       2,  __ushort,  rw, "7002",      &g_application_ssl_port,
        NULL,   NULL,   default_key_tail},

    PARA_END
};

class_para network_para[] = {
    {KEY_HEART_BEAT,            4096,   __str,    r_, NULL,        NULL,
        NULL,   NULL,   default_key_tail},

    PARA_END
};

class_module _modules[] = {
    {SEC_SYSTEM_BASE,       ID_SYSTEM_BASE,     system_base_para,       NULL,       NULL},
    {SEC_APPLICATION,       ID_APPLICATION,     applications_para,      NULL,       NULL},
    {SEC_NETWORK,           ID_NETWORK,         network_para,           NULL,       NULL},
    MODULE_END
};

class_para *get_para_by_id(class_para *para_tables, class_para_head id)
{
    class_para *para = para_tables;
    for ( ; NULL != para->id.name; para++) {
        if(para->id.id == id.id) { return para; }
    }
    return NULL;
}

class_module *get_module_by_id(unsigned char id)
{
    class_module *module = _modules;
    for ( ; NULL != _modules->section; module++) {
        if(module->id == id) { return module; }
    }
    dbg_error("module id err");
    return NULL;
}


bool check_para_key_exist(const char *section, const char *key)
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
bool set_para_key_val(const char *section, const char *key, const char type, char *val, int32_t len)
{
    if (set_key_value(para_ini, section, key, type, val, len)) {
        return ini_save(PARATABLE_INI, para_ini);
    }
    return false;
}
bool get_para_key_val(const char *section, const char *key, const char type, char *val, int32_t len)
{
    return get_key_value(para_ini, section, key, type, val, len);
}

void open_para_ini(void)
{
    FILE *fd = NULL;
    fd = open_file(PARATABLE_INI);
    if (!fd) {
       dbg_error("can not open : [%s]", PARATABLE_INI); 
       return;
    }
    fclose(fd);

    para_ini = ini_parse(PARATABLE_INI);
}

void para_initial(void)
{
    int32_t i = 0;
    int32_t j = 0;
    for (i = 0; NULL != _modules[i].section; i++) {
        if (!check_module_section(_modules[i].section)) {
            create_module_section(_modules[i].section);
        }
        for (j = 0; NULL != _modules[i].para_table[j].id.name; j++) {
            /* need be saved which haves init_val */
            if (_modules[i].para_table[j].init_val) {
                if (!check_para_key_exist(
                            _modules[i].section,
                            _modules[i].para_table[j].id.name)) {
                    ini_para_key(
                            _modules[i].section, 
                            _modules[i].para_table[j].id.name,
                            (char *)_modules[i].para_table[j].init_val);
                    if (_modules[i].para_table[j].address) {
                        strto_type_val(
                            (const char *)_modules[i].para_table[j].init_val,
                            (char *)_modules[i].para_table[j].address,
                            (const char)_modules[i].para_table[j].type, 
                            _modules[i].para_table[j].len);
                    }
                } else if (_modules[i].para_table[j].address) {
                    get_para_key_val(
                            _modules[i].section, 
                            _modules[i].para_table[j].id.name,
                            (const char)_modules[i].para_table[j].type, 
                            (char *)_modules[i].para_table[j].address,
                            _modules[i].para_table[j].len);
                }
            }
        }
    }
    ini_save(PARATABLE_INI, para_ini);
}
