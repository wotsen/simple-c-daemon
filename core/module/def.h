
#ifndef __DEF_H__
#define __DEF_H__

#include <inttypes.h>

#undef offsetof
#define offsetof(TYPE, MEMBER)          ((size_t)&((TYPE *)0)->MEMBER)

/**
 * sizeof_field(TYPE, MEMBER)
 * 
 * @TYPE: The structure containing the field of interest
 * @MEMBER: The field to return the size of
 * */
#undef sizeof_field
#define sizeof_field(TYPE, MEMBER) sizeof((((TYPE *)0)->MEMBER))

/**
 * offsetofend(TYPE, MEMBER)
 * 
 * @TYPE: The type of the structure
 * @MEMBER: The member within the structure to get the end offset of
 * */
#undef offsetofend
#define offsetofend(TYPE, MEMBER) \
        (offsetof(TYPE, MEMBER) + sizeof_field(TYPE, MEMBER))

#undef container_of
#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

#define min(x,y) ({ \
	typeof(x) _x = (x);     \
	typeof(y) _y = (y);     \
	(void) (&_x == &_y);    \
	_x < _y ? _x : _y; })

#define max(x,y) ({ \
	typeof(x) _x = (x);     \
	typeof(y) _y = (y);     \
	(void) (&_x == &_y);    \
	_x > _y ? _x : _y; })

#define min_t(type, a, b) min(((type) a), ((type) b))
#define max_t(type, a, b) max(((type) a), ((type) b))

/* data-type */
#define __bool                          1
#define __schar                          2
#define __uchar                         3
#define __short                         4
#define __ushort                        5
#define __int                           6
#define __uint                          7
#define __long                          8
#define __ulong                         9
#define __llong                         10
#define __ullong                        11
#define __double                        12
#define __str                           13
#define __void                          14

#endif
