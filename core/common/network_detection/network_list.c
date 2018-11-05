/*
 * =====================================================================================
 *
 *       Filename:  network_list.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/01/2018 03:12:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <pthread.h>    /* -lpthread */

#include "network_list.h"

typedef struct {
    struct json_object *udp_data;
    struct list_head list;
}class_udp_recv_list;

static pthread_mutex_t udp_list_lock = PTHREAD_MUTEX_INITIALIZER;			/* 时间读取锁 */
static const size_t LIST_MAX_LEN = 1024;
static size_t _list_len = 0;

LIST_HEAD(udp_recv_json_data);

void push_udp_data_list(struct json_object *recv)
{
    if (_list_len >= LIST_MAX_LEN) {
        json_object_put(recv);
        return;
    }
    class_udp_recv_list *node = (class_udp_recv_list *)
                                malloc(sizeof(class_udp_recv_list));
    node->udp_data = recv;
    INIT_LIST_HEAD(&node->list);

    pthread_mutex_lock(&udp_list_lock);
    list_add_tail(&node->list, &udp_recv_json_data);
    _list_len++;
    pthread_mutex_unlock(&udp_list_lock);
}

struct json_object *pop_udp_data_list(void)
{
    struct json_object *_recv = NULL;
    class_udp_recv_list *node = NULL;

    pthread_mutex_lock(&udp_list_lock);
    if (list_empty_careful(&udp_recv_json_data)) {
        pthread_mutex_unlock(&udp_list_lock);
        return NULL;
    }
    node = list_first_entry(&udp_recv_json_data, class_udp_recv_list, list);
    list_del(&node->list);
    _list_len--;
    pthread_mutex_unlock(&udp_list_lock);

    _recv = node->udp_data;
    free(node);
    return _recv;
}
