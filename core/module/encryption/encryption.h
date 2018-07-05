/******************************************    *******************************

      > File Name: encryption.h

      > Author: Ywl

      > Descripsion:

      > Created Time:     Thu 17 May 2018 06:53:29 PM PDT

      > Modify Time: 

 *********************************    ***************************************/

#ifndef _ENCRYPTION_H
#define _ENCRYPTION_H

#ifdef __cplusplus
extern "C" {
#endif

enum{
	MD5_TYPE = 0,
	SHA256_TYPE,
	SHA512_TYPE,
	DES_EN_TYPE,
	DES_DE_TYPE,
};

#define OWNER_DES_KEY		"yuyuan34"

unsigned char *openssl_lib(unsigned char encrypt_type, const unsigned char *dest_str, 
                        unsigned char *key, unsigned char *md);

#define md5(str, key, md)	openssl_lib(MD5_TYPE, str, key, md)
#define sha256(str, key, md)	openssl_lib(SHA256_TYPE, str, key, md)
#define des_en(str, key, md)	openssl_lib(DES_EN_TYPE, str, key, md)
#define des_de(str, key, md)	openssl_lib(DES_DE_TYPE, str, key, md)

#ifdef __cplusplus
}
#endif

#endif
