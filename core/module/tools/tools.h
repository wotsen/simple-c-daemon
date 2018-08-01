/******************************************    *******************************
      > File Name: tools.h
      > Author: Ywl
      > Descripsion: 一些工具
      > Created Time:     Thu 30 Nov 2017 02:41:55 PM CST
      > Modify Time: 
 *********************************    ***************************************/

#ifndef _TOOLS_H
#define _TOOLS_H

#include <stdbool.h>
#include <inttypes.h>

#define PACKED		__attribute__ ((packed)) /* 结构体对齐 */

/************************************************************************
 * 常用宏函数定义
 *
 * ***********************************************************************/

/* 数组总个数 */
#define ARRAY_SIZE(a)	 (sizeof((a)) / sizeof((a)[0])) 

/* g:总个数, s:每组大小, 返回:分组数 */
#define GROUP_NUM(g, s)	 (((g) + (s) - 1) / (s))	
/* 数组中最后一个元素 */
#define STACK_TOP(stack) (&stack[ARRAY_SIZE(stack)-1])	
/* 取bit0~31 中的某位 */
#define BIT(n)		     (1ul << (n))			



bool system_cmd(const char *cmd, const char *args);
void system_reboot(void);
void *memory_alloc(uint32_t size);
void *memory_realloc(uint32_t now_size, 
                     void *old, void *addr, 
                     uint32_t len);
uint16_t calculate_crc16(uint16_t crc, 
                     uint8_t *ptr, 
                     uint32_t len);
/* 多个字节转换成无符号整型数 */
uint32_t byte_to_int(const uint8_t *byte, uint32_t len);
/* 多个字节转换成有符号整型数 */
int32_t byte_to_sint(const uint8_t *byte, uint32_t len);
char *digit_to_ascii(char *ascii, const uint8_t *digit, uint32_t len);
uint32_t ascii_to_hex(uint8_t *hex, const char *ascii, uint32_t len);

#define MAX_INT8    128
#define MAX_UINT8   (MAX_INT8 * 2 -1)
#define MAX_INT16   32768
#define MAX_UINT16  (MAX_INT16 * 2 -1)
#define MAX_INT32   2147483648
#define MAX_UINT32  (MAX_INT32 * 2 - 1)
#define MAX_INT64   9223372036854775808l
#define MAX_UINT64  18446744073709551615ul

/* 两个字节的数组转换成整型数 */
#define byte_to_word(byte)	byte_to_int(byte, 2)
/* 三个字节的数组转换成整型数 */
#define byte_to_int24(byte)	byte_to_int(byte, 3)
/* 四个字节的数组转换成整型数 */
#define byte_to_long(byte)	byte_to_int(byte, 4)

#endif

