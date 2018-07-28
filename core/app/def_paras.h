/*
 * ============================================================================
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
 * ===========================================================================
 */
#ifndef __DEF_PARAS_H__
#define __DEF_PARAS_H__


/* permission */
#define r_                              1
#define w_                              2
#define rw                              3

/* section */
#define SEC_SYSTEM_BASE                 "system_base"
#define SEC_APPLICATION                 "application"
#define SEC_NETWORK                     "network"

/* para head */

#define default_key_tail                NULL, 0xFFFF, 0, 0, 0

/* modules id */
#define ID_SYSTEM_BASE                  0x1
#define ID_APPLICATION                  0x2
#define ID_NETWORK                      0x3

#endif
