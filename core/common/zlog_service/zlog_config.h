/*
 * =====================================================================================
 *
 *       Filename:  zlog_config.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/05/2018 04:20:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __ZLOG_CONFIG_H__
#define __ZLOG_CONFIG_H__

#include "../file_ops/def_files.h"

#define PROGRAM_DBG         "program"
#define USER_LOG            "user"
#define SYSTEM_LOG          "system"

#define zlog_config  "\
[global]\n\n\
default format = \"date : %%d %%V [pid: %%p %%m%%n\"\n\n\
[formats]\n\n\
simple = \"%%m%%n\"\n\
user_fmt = \"[%%H] date : %%d(%%Z %%F %%A %%B) %%V %%m%%n\"\n\
system_fmt = \"[%%H] date : %%d(%%Z %%F %%A %%B) %%V [pid: %%p %%m%%n\"\n\n\
[rules]\n\n\
program.=DEBUG    >stdout; simple\n\
program.=ERROR    \"/dev/tty\"\n\
program.=FATAL    \"/dev/tty\"\n\
program.=FATAL    \"%sprogram_log.log\", 10MB ~ \"aa-%%d(%%Y%%m%%d).#2s.log\"\n\n\
user.*            \"%suser_log.log\", 10MB ~ \"aa-%%d(%%Y%%m%%d).#2s.log\"; user_fmt\n\n\
system.=INFO      \"/dev/tty\"; user_fmt\n\
system.=INFO      \"%ssystem_log.log\", 10MB ~ \"aa-%%d(%%Y%%m%%d).#2s.log\"; user_fmt\n\
system.!INFO      \"%ssystem_log.log\", 10MB ~ \"aa-%%d(%%Y%%m%%d).#2s.log\"; system_fmt\n"

#endif
