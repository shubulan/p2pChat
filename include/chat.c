/*************************************************************************
	> File Name: include/chat.c
	> Author: shubulan
	> Mail: gaoyulong1996@163.com
	> Created Time: Thu 25 Feb 2021 03:53:50 PM CST
 ************************************************************************/
#include "myhead.h"
extern char *config;
extern char name[20];
extern char msg[512];
extern int port; 

void *client_discover(void *arg) {
    char file[512] = "0";
    FILE *fp;
    struct Msg request;
    strcpy(request.from, name);
    strcpy(request.buff, msg);
    request.type = CHAT_SYN;
    strcpy(file, read_conf(config, "iplist"));
    struct sockaddr_in client;
    int sockfd;
    if ((sockfd = udp_socket()) < 0) {
        perror("udp_socket");
        exit(1);
    }
    if ((fp = fopen(file, "r")) == NULL) {
        perror("fopen");
        exit(1);
    }
    char ip[15];
    DBG("<client discover> starting...\n");
    client.sin_family = AF_INET;
    client.sin_port = htons(port);

    while (~fscanf(fp,"%s", ip)) {
        client.sin_addr.s_addr = inet_addr(ip);
        sendto(sockfd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&client, sizeof(client));
    }
    DBG("<client discover> end!\n");

}
