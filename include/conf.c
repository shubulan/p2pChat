/*************************************************************************
	> File Name: conf.c
	> Author: shubulan
	> Mail: gaoyulong1996@163.com
	> Created Time: Wed 10 Feb 2021 01:51:10 PM CST
 ************************************************************************/

#include "myhead.h"
char value[128];
char *read_conf(const char *path, const char *key) {
    FILE *fp = NULL;
    if (path == NULL || key == NULL) {
        fprintf(stderr, "Error in argument!\n");
        return NULL;
    }
    if ((fp = fopen(path, "r")) == NULL) {
        return NULL;
    }
    char *line = NULL, *sub = NULL;
    ssize_t nread, len;
    while ((nread = getline(&line, &len, fp)) != -1) {
        if ((sub = strstr(line, key)) == NULL) continue;
        if (line[strlen(key)] == '=' && sub == line) {
            strcpy(value, line + strlen(key) + 1);
            value[strlen(value) - 1] = '\0';
        }
    }
    free(line);
    fclose(fp);
    return value;
}
