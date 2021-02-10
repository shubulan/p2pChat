/*************************************************************************
	> File Name: myhead.h
	> Author: shubulan
	> Mail: gaoyulong1996@163.com
	> Created Time: Wed 10 Feb 2021 01:26:21 PM CST
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#include "myudp.h"
#include "conf.h"
#include "color.h"
#include "chat.h"

#ifdef _D
#define DBG(fmt, args...) fprintf(stderr, fmt, ##args)
#else
#define DBG(fmt, args...) 
#endif

#endif
