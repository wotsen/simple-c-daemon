/*
 * =====================================================================================
 *
 *       Filename:  file_ops.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/05/2018 09:53:20 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __FILE_OPS_H__
#define __FILE_OPS_H__

#include <stdbool.h>
#include "../../module/iniparser/iniparser.h"
#include "def_files.h"


void file_fd_initial(void);
FILE *open_file(const char *path);

dictionary *ini_parse(const char *ini_name);
bool create_section(dictionary *dict, const char *section);
bool check_section(dictionary *dict, const char *section);
bool initial_key_value(dictionary *dict, const char *section, const char *key, char *val);
bool set_key_value(dictionary *dict, const char *section, const char *key, const char type, char *val);
bool get_key_value(dictionary *dict, const char *section, const char *key, const char type, char *val, int32_t len);
bool ini_save(const char *ini_name, dictionary *dict);

bool strto_type_val(const char *s, char *val, const char type, int32_t len);

#endif
