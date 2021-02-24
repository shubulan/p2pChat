/*************************************************************************
	> File Name: reactor.c
	> Author: shubulan
	> Mail: gaoyulong1996@163.com
	> Created Time: Wed 24 Feb 2021 03:55:48 PM CST
 ************************************************************************/

#include "myhead.h"

void add_event_ptr(int epollfd, int fd, int events, struct User *user) {
    struct epoll_event ev;
    ev.events = events;
    ev.data.ptr = (void *)user;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

int add_to_reactor(int fd, struct User *user) {
    int sub = user->fd;
    user[sub] = *user;
    add_event_ptr(fd, user[sub].fd, EPOLLIN | EPOLLET, &user[sub]);

}

