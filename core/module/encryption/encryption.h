/******************************************    *******************************

      > File Name: encryption.h

      > Author: Ywl

      > Descripsion:

      > Created Time:     Thu 17 May 2018 06:53:29 PM PDT

      > Modify Time: 

 *********************************    ***************************************/

#ifndef _ENCRYPTION_H
#define _ENCRYPTION_H

#include <inttypes.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

enum{
	MD5_TYPE = 0,
	SHA256_TYPE,
	SHA512_TYPE,
	DES_EN_TYPE,
	DES_DE_TYPE,
    CRYPT_MAX_TYPE,
};

static inline bool check_crypto_type_valid(const uint8_t type)
{
    if (type >= CRYPT_MAX_TYPE) {
        return false;
    }
    return true;
}

#define OWNER_DES_KEY		"yuyuan34"

uint8_t *openssl_lib(uint8_t encrypt_type, const uint8_t *dest_str, 
                           uint8_t *key, uint8_t *md);

#define md5(str, md)	        openssl_lib(MD5_TYPE, str, NULL, md)
#define sha256(str, md)	        openssl_lib(SHA256_TYPE, str, NULL, md)
#define des_en(str, key, md)	openssl_lib(DES_EN_TYPE, str, key, md)
#define des_de(str, key, md)	openssl_lib(DES_DE_TYPE, str, key, md)

#ifdef __cplusplus
}
#endif

#endif
