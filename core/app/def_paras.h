/*
 * =====================================================================================
 *
 *       Filename:  def_paras.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/04/2018 05:22:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __DEF_PARAS_H__
#define __DEF_PARAS_H__


/* permission */
#define R_                              1
#define w_                              2
#define RW                              3

/* section */
#define SEC_SYSTEM_BASE                 "system_base"

/* para head */

#define default_key_tail                NULL, 0xFFFF, 0, 0, 0

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
