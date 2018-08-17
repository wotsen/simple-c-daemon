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

#include <inttypes.h>
#include "../../module/encryption/encryption.h"

void enc_key_setup(const char *key);
uint8_t *enc_md5(const uint8_t *str, uint8_t *md);
uint8_t *enc_sha256(const uint8_t *str, uint8_t *md);
uint8_t *enc_des_en(const uint8_t *str, uint8_t *md);
uint8_t *enc_des_de(const uint8_t *str, uint8_t *md);

#endif
