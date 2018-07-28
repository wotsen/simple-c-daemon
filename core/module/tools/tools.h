/******************************************    *******************************
      > File Name: tools.h
      > Author: Ywl
      > Descripsion: 一些工具
      > Created Time:     Thu 30 Nov 2017 02:41:55 PM CST
      > Modify Time: 
 *********************************    ***************************************/

#ifndef _TOOLS_H
#define _TOOLS_H

#define PACKED		__attribute__ ((packed)) /* 结构体对齐 */

/************************************************************************
 * 常用宏函数定义
 *
 * ***********************************************************************/

/* 数组总个数 */
#define ARRAY_SIZE(a)	(sizeof((a)) / sizeof((a)[0])) 

/* g:总个数, s:每组大小, 返回:分组数 */
#define GROUP_NUM(g, s)	(((g) + (s) - 1) / (s))	

#define STACK_TOP(stack) (&stack[ARRAY_SIZE(stack)-1])	/* 数组中最后一个元素 */
#define BIT(n)		 (1ul << (n))			/* 取bit0~31 中的某位 */



unsigned char system_cmd(const char *cmd, const char *args);
void system_reboot(void);
void *memory_alloc(unsigned int size);
void *memory_realloc(unsigned int now_size, void *old, void *addr, unsigned int len);
unsigned short calculate_crc16(unsigned short crc, unsigned char *ptr, unsigned int len);
/* 多个字节转换成无符号整型数 */
unsigned int byte_to_int(const unsigned char *byte, unsigned int len);
/* 多个字节转换成有符号整型数 */
int byte_to_sint(const unsigned char *byte, unsigned int len);
char *digit_to_ascii(char *ascii, const unsigned char *digit, unsigned int len);
unsigned int ascii_to_hex(unsigned char *hex, const char *ascii, unsigned int len);

#define MAX_INT8    128
#define MAX_UINT8   (MAX_INT8 * 2 -1)
#define MAX_INT16   32768
#define MAX_UINT16  (MAX_INT16 * 2 -1)
#define MAX_INT32   2147483648
#define MAX_UINT32  (MAX_INT32 * 2 - 1)
#define MAX_INT64   9223372036854775808l
#define MAX_UINT64  18446744073709551615ul

#define byte_to_word(byte)	byte_to_int(byte, 2)	/* 两个字节的数组转换成整型数 */
#define byte_to_int24(byte)	byte_to_int(byte, 3)	/* 三个字节的数组转换成整型数 */
#define byte_to_long(byte)	byte_to_int(byte, 4)	/* 四个字节的数组转换成整型数 */

#endif

