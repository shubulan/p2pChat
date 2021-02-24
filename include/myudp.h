/*************************************************************************
	> File Name: myudp.h
	> Author: shubulan
	> Mail: gaoyulong1996@163.com
	> Created Time: Wed 10 Feb 2021 11:53:41 AM CST
 ************************************************************************/

#ifndef _MYUDP_H
#define _MYUDP_H
int udp_socket_s(int port); 
int udp_socket(); 
int udp_accept(int fd, struct User *user);
int udp_connect(struct sockaddr_in *client);
#endif
