/*
 * =====================================================================================
 *
 *       Filename:  enc_wrap.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/05/2018 02:29:51 PM
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
#include <inttypes.h>

#include "enc_wrap.h"

uint8_t g_enc_key[9] = "yuan1314";

void enc_key_setup(const char *key)
{
    if (!key) { return ; }
    sprintf((char *)g_enc_key, "%s", key);
}

uint8_t *enc_md5(const uint8_t *str, uint8_t *md)
{
    if (!str || !md) { return NULL; }
    return md5(str, NULL, md);
}

uint8_t *enc_sha256(const uint8_t *str, uint8_t *md)
{
    if (!str || !md) { return NULL; }
    return sha256(str, NULL, md);
}

uint8_t *enc_des_en(const uint8_t *str, uint8_t *md)
{
    if (!str || !md) { return NULL; }
    return des_en(str, g_enc_key, md);
}

uint8_t *enc_des_de(const uint8_t *str, uint8_t *md)
{
    if (!str || !md) { return NULL; }
    return des_en(str, g_enc_key, md);
}
