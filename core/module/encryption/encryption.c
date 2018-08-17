/******************************************    *******************************

      > File Name: encryption.c

      > Author: Ywl

      > Descripsion:

      > Created Time:     Thu 17 May 2018 06:53:01 PM PDT

      > Modify Time: 

 *********************************    ***************************************/

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/des.h>

#include "encryption.h"

typedef uint8_t *(*encrypt_fun)(
                        const uint8_t *, 
                        size_t len, uint8_t *);
typedef uint8_t *(*abstract_fun)(
                        uint8_t, const uint8_t *, 
                        uint8_t *, uint8_t *);

static uint8_t *_md5__sha256_abstract(
                        uint8_t encrypt_type, 
                        const uint8_t *dest_str, 
                        uint8_t *md)
{

	encrypt_fun encrypt;

    if (!dest_str || !md) { return NULL; }

	uint8_t len = strlen((char *)dest_str);
	int i = 0;
	uint8_t tmp_md[64] = {0};
	char dest_key[128] = {0};
	char char_tmp[3] = {0};

	switch (encrypt_type) {
		case MD5_TYPE:
			encrypt = MD5;
			break;
		case SHA256_TYPE:
			encrypt = SHA256;
			break;
		default:
			return NULL;
	}
	if (!encrypt(dest_str, len, tmp_md)) { return NULL; }
	for (i = 0; i < 32; i++) {
		sprintf(char_tmp, "%02x", tmp_md[i]);
		strcat(dest_key, char_tmp);
	}
	dest_key[32] = '\0';
	memcpy(md, dest_key, 32);
	return md;
}


static uint8_t *_md5_abstract(uint8_t encrypt_type, 
                              const uint8_t *dest_str, 
                              uint8_t *key, uint8_t *md5)
{
	return _md5__sha256_abstract(encrypt_type, dest_str, md5);
}

static uint8_t *_sha256_abstract(uint8_t encrypt_type,
                                 const uint8_t *dest_str, 
                                 uint8_t *key, uint8_t *sha256)
{
	return _md5__sha256_abstract(encrypt_type, dest_str, sha256);
}


#define DES_KEY_LEN	8

static uint8_t *__des_en_de__(int mode, const uint8_t *dest_str, 
                              uint8_t *key, uint8_t *md)
{
	uint8_t vec_cipher_text[512] = {0};
	uint8_t tmp[DES_KEY_LEN] = {0};
	
	int i = 0;
    uint8_t dest_len = strlen((char *)dest_str);
    uint8_t key_len = strlen((char *)key);

	DES_cblock key_encrypt;

	/* 构造8位长度的密钥 */
	memset(key_encrypt, 0, DES_KEY_LEN);
	if (key_len <= DES_KEY_LEN) {
		memcpy(key_encrypt, key, key_len);
	} else {
		memcpy(key_encrypt, key, DES_KEY_LEN);
	}
	/* 密钥置换 */
	DES_key_schedule key_schedule;
	DES_set_key_unchecked(&key_encrypt, &key_schedule);

	const_DES_cblock input_text;
	DES_cblock output_text;

	for (i = 0; i < dest_len / DES_KEY_LEN; i++) {
		memcpy(input_text, dest_str+i*DES_KEY_LEN, DES_KEY_LEN);
		DES_ecb_encrypt(&input_text, &output_text, &key_schedule, mode);
		memcpy(tmp, output_text, DES_KEY_LEN);

		memcpy(vec_cipher_text+i*DES_KEY_LEN, tmp, DES_KEY_LEN);
	}

	if (dest_len % DES_KEY_LEN != 0) {
		int tmp1 = dest_len / DES_KEY_LEN * DES_KEY_LEN;
		int tmp2 = dest_len - tmp1;
		memset(input_text, 0, DES_KEY_LEN);
		memcpy(input_text, dest_str+tmp1, tmp2);

		DES_ecb_encrypt(&input_text, &output_text, &key_schedule, mode);
		memcpy(tmp, output_text, DES_KEY_LEN);

		memcpy(vec_cipher_text+i*DES_KEY_LEN, tmp, DES_KEY_LEN);
		i++;
	}
	memcpy(md, vec_cipher_text, i*DES_KEY_LEN);

	return md;
}
static uint8_t *__des_encrypt(const uint8_t *dest_str,
                                    uint8_t *key, uint8_t *md)
{
	return __des_en_de__(DES_ENCRYPT, dest_str, key, md);
}
static uint8_t *__des_decrypt(const uint8_t *dest_str,
                                    uint8_t *key, uint8_t *md)
{
	return __des_en_de__(DES_DECRYPT, dest_str, key, md);
}

static uint8_t *_des_encrypt(uint8_t encrypt_type, 
                                     const uint8_t *dest_str, 
                                     uint8_t *key, uint8_t *md)
{
	return __des_encrypt(dest_str, key, md);
}
static uint8_t *_des_decrypt(uint8_t encrypt_type, 
                                     const uint8_t *dest_str, 
                                     uint8_t *key,uint8_t *md)
{
	return __des_decrypt(dest_str, key, md);
}

uint8_t *openssl_lib(uint8_t encrypt_type, 
                     const uint8_t *dest_str, 
                     uint8_t *key, uint8_t *md)
{
	abstract_fun abstract;

	switch (encrypt_type) {
		case MD5_TYPE:
			abstract = _md5_abstract;
			break;
		case SHA256_TYPE:
			abstract = _sha256_abstract;
			break;
		case DES_EN_TYPE:
			abstract = _des_encrypt;
			break;
		case DES_DE_TYPE:
			abstract = _des_decrypt;
			break;
		default:
			return NULL;
	}

	return abstract(encrypt_type, dest_str, key, md);
}


#if 0
int main()
{
	uint8_t md[33] = {0};
	uint8_t md2[33] = {0};
	const char *pass = "password_key";

	md5(pass, "yuanyuan", md);

	printf("md5: %s\n", md);

	memset(md, 0, sizeof(md));
	sha256(pass, "yuanyuan", md);

	printf("sha256: %s\n", md);

	memset(md, 0, sizeof(md));
	des_en(pass,"yuanyuan",  md);

	printf("des: %s\n", md);

	des_de(md,"yuanyuan",  md2);

	printf("des: %s\n", md2);
	return 0;
}
#endif
