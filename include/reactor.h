/*************************************************************************
	> File Name: reactor.h
	> Author: shubulan
	> Mail: gaoyulong1996@163.com
	> Created Time: Wed 24 Feb 2021 03:54:37 PM CST
 ************************************************************************/

#ifndef _REACTOR_H
#define _REACTOR_H
int add_to_reactor(int subfd, struct User *newuser);
int del_from_reactor(int subfd, struct User *newuser);
void *sub_reactor(void *args);
#endif
