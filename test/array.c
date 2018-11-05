/*
 * =====================================================================================
 *
 *       Filename:  array.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/03/2018 08:44:14 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct st_1 {
    int a;
    int b[];
};

struct st_2 {
    int a;
    int b[0];
};

struct st_3 {
    int a;
    int b[1];
};

void fun_print(char *s)
{
    char buf[strlen(s)];
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", s);

    printf("input-str = [%s]\nlocal-str = [%s]\n", s, buf);
}

int main()
{
    char array[127] = { [0 ... 126] = 1 };
    fun_print((char *)"hello array");

    for ( size_t i = 0; i < sizeof(array); i++) {
        //printf("array[%zu]=%d, ", i, array[i]);
        //if (!(i % 6)) { printf("\n"); }
    }
    printf("\n");
    printf("st_1-size=[%zu]\n", sizeof(struct st_1));
    printf("st_2-size=[%zu]\n", sizeof(struct st_2));
    printf("st_3-size=[%zu]\n", sizeof(struct st_3));
    return 0;
}
