#ifdef UNIT_TESTING
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <inttypes.h>
#include <google/cmockery.h>
#include "encryption.h"

const char *_key = "unit_testing";
const char *_password = "123";

void md5_test(void** state)
{
    const char *md5_123 = "202cb962ac59075b964b07152d234b70";
    uint8_t md[33] = { [0 ... 32] = '\0' };
    assert_string_equal(md5((uint8_t* )_password, md),
                        (uint8_t* )md5_123);
}


void sha256_test(void** state)
{
    const char *sha256_123 = "a665a45920422f9d417e4867efdc4fb8a04a1f3fff1fa07e998e86f7f7a27ae3";
    uint8_t md[65] = { [0 ... 64] = '\0' };
    assert_string_equal(sha256((uint8_t* )_password, md),
                        (uint8_t* )sha256_123);
}

#if 0
const char *des_pass = "84932742752";
void des_en_test(void** state)
{
    uint8_t md[65] = { [0 ... 64] = '\0' };
    des_en((uint8_t* )des_pass, (uint8_t* )_key, md);
    for (size_t i = 0; i < sizeof(md); i++) {
        printf("%d\n", md[i]);
    }
}
#endif

int main(int argc, char** argv)
{
    const UnitTest tests[] = {
        unit_test(md5_test),
        unit_test(sha256_test),
    //    unit_test(des_en_test),
    };
    return run_tests(tests);
}

#endif
