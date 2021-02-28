/*************************************************************************
	> File Name: include/heart.c
	> Author: shubulan
	> Mail: gaoyulong1996@163.com
	> Created Time: Fri 26 Feb 2021 10:39:31 AM CST
 ************************************************************************/

#include "myhead.h"

extern struct User *users;
extern char name[20];
void *heart_beat(void *arg) {
    struct Msg heart;
    heart.type = CHAT_HEART;
    strcpy(heart.from, name);
    heart.type = CHAT_HEART;
    while (1) {
        for (int i = 0; i < MAX_USR; i++) {
            if (users[i].flag == FL_ONLINE) {
                if (users[i].heart_cnt >= 5) {
                    DBG(L_RED"<heart beat>"NONE"%s is offline.", users->name);
                    users[i].flag = FL_OFFLINE;
                    del_from_reactor(users[i].fd, &users[i]);
                    DBG(L_RED"<heart beat>"NONE"del %s from sub reactor.", users->name);
                }
                users[i].heart_cnt++;
                send(users[i].fd, (void *)&heart, sizeof(heart), 0);
            }
        }
        sleep(60);
    }
}
