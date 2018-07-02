/******************************************    *******************************

      > File Name: user_pass.h

      > Author: Ywl

      > Descripsion:

      > Created Time:     Sat 23 Jun 2018 07:10:29 PM CST

      > Modify Time: 

 *********************************    ***************************************/

#ifndef _USER_PASS_H
#define _USER_PASS_H

#define USER_PASSWOR_DB_PATH    "./system/etc/user_password.db"
#define CORE_USER_VERI_DB_NAME          "coreuser"

#define DATABASE_LOW        0
#define DATABASE_MD5        1
#define DATABASE_SHA256     2

bool core_password_veri(char secu_lv, const char *user, const char *password);

#define core_veri_sha256(user, password)        core_password_veri(DATABASE_SHA256, user, password)
#define core_veri(user, password)               core_password_veri(DATABASE_LOW, user, password)

#endif
