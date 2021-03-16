/*************************************************************************
	> File Name: chat_ui.h
	> Author: shubulan
	> Mail: gaoyulong1996@163.com
	> Created Time: Fri 12 Mar 2021 09:45:05 PM CST
 ************************************************************************/

#ifndef _CHAT_UI_H
#define _CHAT_UI_H
#include "myhead.h"
#define MAX_MSG 1024
void init_ui();
void drawMain();
void drawSub();
extern pthread_mutex_t mainMutex;
extern char *chatMsg[MAX_MSG];
extern char *userName[MAX_MSG];
extern int msgTail;
extern int userTail;
#endif
