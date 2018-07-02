/******************************************    *******************************

      > File Name: user_pass.c

      > Author: Ywl

      > Descripsion:

      > Created Time:     Sat 23 Jun 2018 07:03:18 PM CST

      > Modify Time: 

 *********************************    ***************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#define __unit_test__ 0

#include "../../module/bool.h"
#if !__unit_test__
#include "../../module/zlog_service/zlog_service.h"
#include "../../module/encryption/encryption.h"
#endif
#include "user_pass.h"

static int callback_veri(void *data, int argc, char **argv, char **azColName)
{
    return (argc > 0 ? 0 : -1);
}

bool core_password_veri(char secu_lv, const char *user, const char *password)
{
    sqlite3 *db;
    char sql[1024];
    unsigned char md[40];
    if(!user || !password)
    {
        return false;
    }
    switch(secu_lv)
    {
        case DATABASE_LOW:
            sprintf((char *)md, "%s", password);
            break;
        case DATABASE_SHA256:
            if(sha256((const unsigned char *)password, md) == NULL)
                return false;
            break;
        default:
            return false;
    }
    sprintf(sql, "select user, password from %s where user='%s' and password='%s';", \
            CORE_USER_VERI_DB_NAME, user, md);
    if(sqlite3_open(USER_PASSWOR_DB_PATH, &db) < 0)
    {
#if !__unit_test__
        system_log(LV_ERROR, "can not open %s\r\n", USER_PASSWOR_DB_PATH);
#endif
        return false;
    }
    if(sqlite3_exec(db, sql, callback_veri, NULL, NULL) != SQLITE_OK)
    {
        sqlite3_close(db);
#if !__unit_test__
        dbg_error("%s :error\r\n", sql);
#endif
        return false;
    }
    sqlite3_close(db);
    return true;
}

#if __unit_test__
int main()
{
    const char *user = "admin";
    const char *password = "<Core-Admin-2018-Sqlite>";
    printf("veri result: %d \r\n", core_password_veri(user, password));
}
#endif

#undef __unit_test__
