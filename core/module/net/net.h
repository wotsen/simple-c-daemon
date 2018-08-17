/******************************************    *******************************
  > File Name: net.h
  > Author: Ywl
  > Descripsion: 网络通信部分的配置
  > Created Time:     Thu 30 Nov 2017 02:16:36 PM CST
  > Modify Time: 
 *********************************    ***************************************/

#ifndef _NET_H
#define _NET_H

#include <arpa/inet.h>
#include <net/if.h>
#include <sys/socket.h>
#include <inttypes.h>

/* 将网络二进制的数字转换成网络地址 */
#define INET_NTOA(ip)		\
        ip & 0xFF, (ip >> 8) & 0xFF, (ip >> 16) & 0xFF, (ip >> 24) & 0xFF

#define NET_UDP_MODULE_EN			1					/* UDP网络通信 */
#define NET_TCP_MODULE_EN			1					/* TCP网络通信 */

#define UDP_DATA_TYPE				0x1
#define TCP_DATA_TYPE				0x2

#define UBUNTU_UDP_SERVER_EN		1
#define MASTER_UDP_SERVER_PORT		111314				/* 主服务器UDP端口号 */
#define CGI_UDP_CLIENT_PORT			111315				/* 主服务器UDP端口号 */
/* UDP数据解析 */
void unpack_udpdata(char *data, int32_t len, char *ip, uint16_t port);
/* UDP 套接字创建 */
int32_t udpsock_create(char *eth, char *ip, uint16_t port, uint32_t sendtime, uint32_t recvtime);
/* UDP发送 */
int32_t udpsock_send(int32_t fd, uint8_t *ip, uint16_t port, char *data, uint32_t len);

/* UDP数据解析 */
void unpack_tcpdata(char *data, int32_t len, char *ip, uint16_t port);

/* 数据类型解析 */
void unpack_netdata(char *data, int32_t len, char *ip, uint16_t port);

#endif

