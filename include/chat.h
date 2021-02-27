/************************************************************************
	> File Name: chat.h
	> Author: shubulan
	> Mail: gaoyulong1996@163.com
	> Created Time: Wed 10 Feb 2021 05:45:16 PM CST
 ************************************************************************/

#ifndef _CHAT_H
#define _CHAT_H
#define MAX_USR 500
#define FL_SYNSENT 0x001
#define FL_ONLINE 0x002
#define FL_OFFLINE 0x003
struct User {
    char name[20];
    char ip[20];
    int flag;
    int fd;
    int heart_cnt;
};

#define CHAT_SYN 0x001
#define CHAT_ACK 0x002
#define CHAT_FIN 0x004
#define CHAT_HEART 0x008
#define CHAT_MSG 0x010
struct Msg {
    int type;
    char from[20];
    char to[20];
    char buff[1024];
};
void *client_discover(void *arg);
void logout(int signum);
#endif
