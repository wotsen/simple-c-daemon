/*
 * =====================================================================================
 *
 *       Filename:  enc_wrap.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/05/2018 02:30:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __ENC_WRAP_H__
#define __ENC_WRAP_H__

#include "../../module/encryption/encryption.h"

unsigned char *enc_md5(const unsigned char *str, unsigned char *md);
unsigned char *enc_sha256(const unsigned char *str, unsigned char *md);
unsigned char *enc_des_en(const unsigned char *str, unsigned char *md);
unsigned char *enc_des_de(const unsigned char *str, unsigned char *md);

#endif
