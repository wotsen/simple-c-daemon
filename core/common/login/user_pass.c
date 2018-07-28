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
#include <stdbool.h>
#include <inttypes.h>


#include "../zlog_service/zlog_service.h"
#include "../enc_wrap/enc_wrap.h"
#include "user_pass.h"

static int32_t callback_veri(void *data, int32_t argc,
                             char **argv, char **azColName)
{
    return (argc > 0 ? 0 : -1);
}

bool core_password_veri(char secu_lv, const char *user, 
                        const char *password)
{
    sqlite3 *db;
    char sql[1024];
    uint8_t md[40];

    if(!user || !password) { return false; }
    switch(secu_lv)
    {
        case DATABASE_LOW:
            sprintf((char *)md, "%s", password);
            break;
        case DATABASE_SHA256:
            if(!enc_sha256((const uint8_t *)password, md)) {
                return false;
            }
            break;
        default:
            return false;
    }
    sprintf(sql, 
            "select user, password from %s where user='%s' and password='%s';",
            CORE_USER_VERI_DB_NAME, user, md);
    if(sqlite3_open(USER_PASSWOR_DB_PATH, &db) < 0)
    {
        system_log(LV_ERROR, "can not open %s\r\n", USER_PASSWOR_DB_PATH);
        return false;
    }
    if(sqlite3_exec(db, sql, callback_veri, NULL, NULL) != SQLITE_OK)
    {
        sqlite3_close(db);
        dbg_error("%s :error\r\n", sql);
        return false;
    }
    sqlite3_close(db);

    return true;
}

