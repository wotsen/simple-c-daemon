/******************************************    *******************************

      > File Name: zlog_service.h

      > Author: Ywl

      > Descripsion:

      > Created Time:     Mon 07 May 2018 01:44:54 AM PDT

      > Modify Time: 

 *********************************    ***************************************/

#ifndef _ZLOG_SERVICE_H
#define _ZLOG_SERVICE_H


#include <zlog.h>

#define LV_DEBUG    ZLOG_LEVEL_DEBUG
#define LV_INFO     ZLOG_LEVEL_INFO
#define LV_NOTICE   ZLOG_LEVEL_NOTICE
#define LV_WARN     ZLOG_LEVEL_WARN
#define LV_ERROR    ZLOG_LEVEL_ERROR
#define LV_FATAL    ZLOG_LEVEL_FATAL


void _system_log(char lv, const char *format, ...);
void _user_log(char lv, const char *format, ...);
void _dbg_log(char lv, const char *format, ...);

#define dbg_print(fmt, args...)     \
        _dbg_log(LV_DEBUG, fmt, ##args)
#define dbg_error(fmt, args...)     \
        _dbg_log(LV_ERROR, "file: %s fun: %s line : %d] " fmt,\
                  __FILE__, __func__,  __LINE__, ##args)
#define dbg_log(fmt, args...)       \
        _dbg_log(LV_FATAL, "file: %s fun: %s line : %d] " fmt,\
                  __FILE__, __func__,  __LINE__, ##args)

#define system_log(lv, fmt, args...) \
        _system_log(lv, "file: %s fun: %s line : %d] " fmt,   \
                     __FILE__, __func__,  __LINE__, ##args)
#define user_log(lv, fmt, args...)   \
        _user_log(lv, "file: %s fun: %s line : %d] " fmt,     \
                   __FILE__, __func__,  __LINE__, ##args)
#define system_info(fmt, args...)   \
        _system_log(LV_INFO, fmt, ##args)

#endif

