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
    mainWin = newwin(Y - INPUTH - 2, XMID - 1 - 2, 1, 1);
    subWin = newwin(Y - 2, X - XMID - 2, 1, XMID + 1);
    inputWin = newwin(INPUTH - 2, XMID - 1 - 2, Y - INPUTH + 1, 1);
    mvwprintw(mainWin, 0, 0 ,"here");
    mvwprintw(subWin, 0, 0 ,"here");
    mvwprintw(inputWin, 0, 0 ,"here");
    wrefresh(mainWin);
    wrefresh(subWin);
    wrefresh(inputWin);


    return ;
}
