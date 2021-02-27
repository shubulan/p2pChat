/*************************************************************************
	> File Name: include/heart.c
	> Author: shubulan
	> Mail: gaoyulong1996@163.com
	> Created Time: Fri 26 Feb 2021 10:39:31 AM CST
 ************************************************************************/

#include "myhead.h"

extern struct User *users;
void *heart_beat(void *arg) {
    struct Msg heart;
    heart.type = CHAT_HEART;
    while (1) {
        for (int i = 0; i < MAX_USR; i++) {
            if (users[i].flag) {
                send(users[i].fd, (void *)&heart, sizeof(heart), 0);
            }
        }
        sleep(2);
    }
}
