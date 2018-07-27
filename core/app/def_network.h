/*
 * =====================================================================================
 *
 *       Filename:  def_network.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/10/2018 10:24:28 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __NETWORK_H__
#define __NETWORK_H__

#define LOCAL_SYNC_MODULE       0x0001
#define NET_SYNC_MODULE         0x0002

#define KEY_HEART_BEAT                  {"heart beat", 0x0001}


struct json_object *pack_heart_beat(void);

#endif
