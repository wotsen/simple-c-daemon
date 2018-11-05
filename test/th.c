/*
 * =====================================================================================
 *
 *       Filename:  th.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/03/2018 09:16:33 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <threads.h>

int *fun(void *arg)
{
    int i = 0;
    while (i < 4) {
        printf("thread run [%d]\n", i);
        i++;
    }
}

int main()
{
    thrd_t thr;
    int a = 10 + 90;
    thrd_create(&thr, &fun, NULL);
    thrd_join(thr, NULL);
    printf("exit\n");
    return 0;
}
