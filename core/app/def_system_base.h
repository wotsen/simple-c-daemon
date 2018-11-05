/*
 * =====================================================================================
 *
 *       Filename:  def_system_base.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/07/2018 02:57:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _DEF_SYSTEM_BASE_H
#define _DEF_SYSTEM_BASE_H

#define KEY_OS_TYPE                     {"os-type", 0x0001}

/* base-dir */
#define KEY_CONF_DIR                    {"configuration-dir", 0x0002}
#define KEY_DOC_BASE_DIR                {"doc-base-dir", 0x0003}
#define KEY_ETC_BASE_DIR                {"etc-base-dir", 0x0004}

/* log */
#define KEY_SYS_LOG_DIR                 {"log-file-dir", 0x0005}
#define KEY_LOG_CONF_DIR                {"log-configuration-dir", 0x0006}
#define KEY_LOG_CONFIG_FILE             {"log-configuration", 0x0007}

/* databse */
#define KEY_DATBASE_DIR                 {"database-dir", 0x0008}

/* para.ini */
#define KEY_PARA_INI_FILE               {"paratable-ini-file", 0x0009}

#endif
