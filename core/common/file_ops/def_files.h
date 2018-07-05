/*
 * =====================================================================================
 *
 *       Filename:  def_files.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/05/2018 03:56:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __DEF_FILES_H__
#define __DEF_FILES_H__

/* file path */
#define BASE_PATH                       "./system/"
#define DOC_PATH                        BASE_PATH"doc/"
#define ETC_PATH                        BASE_PATH"etc/"

/* doc */
#define LOG_PATH                        DOC_PATH"system_log/"

/* etc */
#define SYS_CONF_PATH                   ETC_PATH"system_conf/"
#define DATABASE_PATH                   ETC_PATH"database/"


#define PARATABLE_INI                   SYS_CONF_PATH"para.ini"
#define SYSTEM_LOG_CONF                 SYS_CONF_PATH"system_log.conf"

#endif
