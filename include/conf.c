/*************************************************************************
	> File Name: conf.c
	> Author: shubulan
	> Mail: gaoyulong1996@163.com
	> Created Time: Wed 10 Feb 2021 01:51:10 PM CST
 ************************************************************************/

#include "head.h"

char *get_value(const char *path, const char *key) {
    FILE *fp = NULL;
    if (path == NULL || key == NULL) {
        fprintf(stderr, "Error in argument!\n");
        return NULL;
    }

}
