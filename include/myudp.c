/*************************************************************************
	> File Name: myudp.c
	> Author: shubulan
	> Mail: gaoyulong1996@163.com
	> Created Time: Wed 10 Feb 2021 12:51:12 PM CST
 ************************************************************************/
#include "myhead.h"
extern int port;
extern char name[20];

int udp_socket_s(int port){
    int listener;
    if ((listener = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return -1;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);
//地址重用
    unsigned long opt = 1;
    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(listener, (struct sockaddr *)&server, sizeof(server)) < 0) {
        return -1;
    }
    return listener;
}

int udp_socket() {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return -1;
    }
    return sockfd;
}
int udp_connect(struct sockaddr_in *client) {
    int sockfd;
    if ((sockfd = udp_socket_s(port)) < 0) {
        return -1;
    }
    client->sin_port = htons(port);
    if (connect(sockfd, (struct sockaddr *)client, sizeof(struct sockaddr_in)) < 0) {
        return -1;
    }
    return sockfd;
}

int udp_accept(int fd, struct User *user) {
    int new_fd;
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    struct Msg request, response;
    bzero(&request, sizeof(request));
    bzero(&response, sizeof(response));

    int ret = recvfrom(fd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&client, &len); 

    if (ret != sizeof(request)) {
        response.type = CHAT_FIN; 
        strcpy(response.buff, "Login Request Error!");
        sendto(fd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&client, len);
        return -1;
    }

    /*
    if (check_online(&request)) {
        response.type = CHAT_FIN;
        strcpy(response.msg, "Already lonin!");
        sendto(fd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&client, len);
        return -1;
    }
    */
    if (!(request.type & CHAT_SYN)) {
        response.type = CHAT_FIN; 
        DBG("<main reactor> none syn recieved : %s\n", request.buff);
        strcpy(response.buff, " request isn't SYN!");
        sendto(fd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&client, len);
        return -1;
    }
    //至此一定收到了syn 或者syn+ack包，此时建立连接
    userName[userTail++] = strdup(request.from);
    drawSub();
    strcpy(user->name, request.from);
    user->flag = FL_ONLINE;
    user->heart_cnt = 0;
    new_fd = udp_connect(&client);
    if (new_fd < 0) {
        perror("udp_connect");
        return -1;
    }
    user->fd = new_fd;

    if (request.type & CHAT_ACK) {
        //收到SYN+ACK的逻辑
        DBG(L_GREEN"<main reactor>"NONE" : %s's SYNACK recieved!\n", request.from); 
    } else {
        //收到SYN包的逻辑
        DBG(L_GREEN"<main reactor>"NONE" %s's SYN recieved!\n", request.from);
        DBG("  Msg: %s\n", request.buff);
        response.type = CHAT_ACK | CHAT_SYN;
        sprintf(response.buff, "%s Login success!\n", user->name);
        strcpy(response.from, name);
        send(new_fd, (void *)&response, sizeof(response), 0);
    }
    return new_fd;
}

