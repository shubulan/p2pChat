/*************************************************************************
	> File Name: chat_ui.c
	> Author: shubulan
	> Mail: gaoyulong1996@163.com
	> Created Time: Fri 12 Mar 2021 09:45:44 PM CST
 ************************************************************************/

#include "myhead.h"
#define X 100
#define Y 30

#define INPUTH 6
#define XMID X * 0.8
WINDOW *box1Win, *box2Win , *box3Win;
WINDOW *mainWin, *subWin , *inputWin;
pthread_mutex_t mainMutex;

char *chatMsg[MAX_MSG];
int mainX = Y - INPUTH - 2;
int msgTail = 0;

void init_ui() {
    setlocale(LC_ALL, "");
    initscr();
    refresh();
    box1Win = newwin(Y - INPUTH, XMID - 1, 0, 0);
    box2Win = newwin(Y, X - XMID, 0, XMID);
    box3Win = newwin(INPUTH, XMID - 1, Y - INPUTH, 0);
    box(box1Win, 0, 0);
    box(box2Win, 0, 0);
    box(box3Win, 0, 0);
    wrefresh(box1Win);
    wrefresh(box2Win);
    wrefresh(box3Win);
    pthread_mutex_init(&mainMutex, NULL);
    mainWin = newwin(mainX, XMID - 1 - 2, 1, 1);
    subWin = newwin(Y - 2, X - XMID - 2, 1, XMID + 1);
    inputWin = newwin(INPUTH - 2, XMID - 1 - 2, Y - INPUTH + 1, 1);
    //mvwprintw(mainWin, 0, 0 ,"here");
    //mvwprintw(subWin, 0, 0 ,"here");
    //mvwprintw(inputWin, 0, 0 ,"here");
    wrefresh(mainWin);
    wrefresh(subWin);
    wrefresh(inputWin);
    return ;
}
void drawMain() {
    int beg;
    pthread_mutex_lock(&mainMutex);
    if (msgTail < mainX) beg = 0;
    else beg = msgTail - mainX;

    for (int i = 0; i < msgTail; i++) {
        mvwprintw(mainWin, i, 2, chatMsg[beg + i]);
    }
    pthread_mutex_unlock(&mainMutex);
    wrefresh(mainWin);

    return ;
}
