/*
 * =====================================================================================
 *
 *       Filename:  regexs.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/22/2018 09:46:49 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ywl
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <regex.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "regexs.h"


bool regex_match_string(const char *pattern, const char *data, char **match)
{
    if(!pattern) { return false; }
    int32_t i = 0;
    int32_t len;

    regex_t reg;
    regmatch_t pmatch[REGEXS_NM];

    if(regcomp(&reg, pattern, REG_EXTENDED) < 0) { return false; }
    if(regexec(&reg, data, REGEXS_NM, pmatch, 0))
    {
        regfree(&reg);
        return false;
    }
    for(i = 0; i < REGEXS_NM && pmatch[i].rm_so != 1; i++)
    {
        len = pmatch[i].rm_eo-pmatch[i].rm_so;
        if(len)
        {
            memset(match[i], 0, 1024);
            memcpy(match[i], data+pmatch[i].rm_so, len);
        }
    }
    regfree(&reg);
    return true;
}

bool regex_match_file(const char *pattern, FILE *fd, char **match)
{
    if(!pattern) { return false; }
    int32_t i = 0;
    int32_t len, err;
    char buf[1024];

    regex_t reg;
    regmatch_t pmatch[REGEXS_NM];

    if(regcomp(&reg, pattern, REG_EXTENDED) < 0) { return false; }
    for(memset(buf, 0, sizeof(buf)); NULL != fgets(buf, sizeof(buf), fd);)
    {
        err = regexec(&reg, buf, REGEXS_NM, pmatch, 0);
        if(err == REG_NOMATCH)
        {
            continue;
        }
        else if(err)
        {
            regfree(&reg);
            return false;
        }
        for(i = 0; i < REGEXS_NM && pmatch[i].rm_so != 1; i++)
        {
            len = pmatch[i].rm_eo-pmatch[i].rm_so;
            if(len)
            {
                memset(match[i], '\0', 1024);
                memcpy(match[i], buf+pmatch[i].rm_so, len);
            }
        }
        memset(buf, 0, sizeof(buf));
    }
    regfree(&reg);
    return true;
}
