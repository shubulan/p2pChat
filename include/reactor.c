/*************************************************************************
	> File Name: reactor.c
	> Author: shubulan
	> Mail: gaoyulong1996@163.com
	> Created Time: Wed 24 Feb 2021 03:55:48 PM CST
 ************************************************************************/

#include "myhead.h"

extern struct User *users;
extern int subfd;
void add_event_ptr(int epollfd, int fd, int events, struct User *user) {
    struct epoll_event ev;
    ev.events = events;
    ev.data.ptr = (void *)user;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

int add_to_reactor(int fd, struct User *user) {
    int sub = user->fd;
    users[sub] = *user;
    add_event_ptr(fd, users[sub].fd, EPOLLIN | EPOLLET, &users[sub]);
}
int del_from_reactor(int fd, struct User *user) {
    epoll_ctl(subfd, EPOLL_CTL_DEL, fd, NULL);
    return 1;
}
void *sub_reactor(void *args) {
    struct epoll_event events[20];
    struct Msg msg;
    while (1) {
        int nfds = epoll_wait(subfd, events, 20, -1);
        if (nfds < 0) exit(1);
        for (int i = 0; i < nfds; i++) {
            int fd = ((struct User *)events[i].data.ptr)->fd;
            recv(fd, &msg, sizeof(msg), 0);
            users[fd].heart_cnt = 0;
            if (msg.type & CHAT_HEART) {
                DBG(L_RED"<sub reactor>"NONE" heart from %s\n", msg.from);   
                msg.type = CHAT_ACK;
                send(fd, &msg, sizeof(msg), 0);
            } else if (msg.type & CHAT_ACK) {
                if (msg.type & CHAT_SYN) continue;
                DBG(L_RED"<sub reactor>"NONE" ACK from %s\n", msg.from);
            } else if (msg.type & CHAT_FIN){
                DBG(L_RED"<sub reactor>"NONE" FIN from %s Good Bye!\n", msg.from);
                del_from_reactor(fd, &users[i]);
                close(fd);
                users[fd].flag = FL_OFFLINE;
                DBG(L_RED"<sub reactor>"NONE" %s is leaving..", msg.from);
            } else if (msg.type & CHAT_MSG) {
                DBG(L_RED"<sub reactor>"NONE" msg from %s:%s\n", msg.from, msg.buff);
                printf(L_BLUE"<%s> :"NONE" %s", msg.from, msg.buff);
            } else {
                DBG(L_RED"<sub reactor>"NONE" unkonw msg\n");
            }
        }
    }
}

