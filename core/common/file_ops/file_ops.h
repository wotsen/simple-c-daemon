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
#include "../../module/bool.h"
#include "../../module/iniparser/iniparser.h"
#include "def_files.h"


void file_fd_initial(void);
FILE *__open_file(const char *path);

dictionary *__ini_parse(const char *ini_name);
bool create_section(dictionary *dict, const char *section);
bool set_key_value(dictionary *dict, const char *section, const char *key, const char type, char *val);
bool get_key_value(dictionary *dict, const char *section, const char *key, const char type, char *val, int len);
bool __ini_save(const char *ini_name, dictionary *dict);

#endif
