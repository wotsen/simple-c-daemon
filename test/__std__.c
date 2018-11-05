/*
 * =====================================================================================
 *
 *       Filename:  __std__.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/20/2018 10:45:40 AM
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

int main()
{
    printf("std:%d, date:%s, time:%s\n", __STDC__, __DATE__, __TIME__);
}
