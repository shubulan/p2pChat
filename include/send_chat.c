/*************************************************************************
	> File Name: send_chat.c
	> Author: shubulan
	> Mail: gaoyulong1996@163.com
	> Created Time: Fri 26 Feb 2021 05:32:36 PM CST
 ************************************************************************/

#include "myhead.h"
extern char name[20];
extern WINDOW *inputWin;
extern struct User *users;
char inputmsg[2046]; 
void *send_chat(void *arg) {
    struct Msg msg;
    strcpy(msg.from, name);
    msg.type = CHAT_MSG;

    while (1) {
        memset(msg.buff, 0, sizeof(msg.buff));
        wclear(inputWin);
        mvwprintw(inputWin, 1, 0, "Input: ");
        wrefresh(inputWin);
        wscanw(inputWin, "%s", msg.buff);
        memset(inputmsg, 0, 2046);
        sprintf(inputmsg,"%s: %s", name, msg.buff);
        pthread_mutex_lock(&mainMutex);
        chatMsg[msgTail] = strdup(inputmsg);
        msgTail++;
        pthread_mutex_unlock(&mainMutex);
        drawMain();

        for (int i = 0; i < MAX_USR; i++) {
            if (users[i].flag) {
                send(users[i].fd, &msg, sizeof(msg), 0);
            }
        }
    }
}

