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

#include "enc_wrap.h"

unsigned char g_enc_key[9] = "yuan1314";

unsigned char *enc_md5(const unsigned char *str, unsigned char *md)
{
    return md5(str, NULL, md);
}

unsigned char *enc_sha256(const unsigned char *str, unsigned char *md)
{
    return sha256(str, NULL, md);
}

unsigned char *enc_des_en(const unsigned char *str, unsigned char *md)
{
    return des_en(str, g_enc_key, md);
}

unsigned char *enc_des_de(const unsigned char *str, unsigned char *md)
{
    return des_en(str, g_enc_key, md);
}
