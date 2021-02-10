/*************************************************************************
	> File Name: chat.h
	> Author: shubulan
	> Mail: gaoyulong1996@163.com
	> Created Time: Wed 10 Feb 2021 05:45:16 PM CST
 ************************************************************************/

#ifndef _CHAT_H
#define _CHAT_H
struct User {
    char name[20];
    char ip[20];
    int flag;
    int fd;
    int heart_cnt;
};
#endif
