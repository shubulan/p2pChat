/*************************************************************************
	> File Name: p2pchat.c
	> Author: shubulan
	> Mail: gaoyulong1996@163.com
	> Created Time: Wed 10 Feb 2021 01:44:13 PM CST
 ************************************************************************/

#include "myhead.h" 
#define MAX_N 10
#define MAX_USR 500

char *config = "./chat.conf";
int port;
char name[20] = {0}, msg[512] = {0};
struct User users[MAX_USR];

int main(int argc, char **argv) {
    int opt;
    while ((opt = getopt(argc, argv, "p:n:m")) != -1) {
        switch (opt) {
            case 'p':
                port = atoi(optarg);
                break;
            case 'm':
                strcpy(msg, optarg);
                break;
            case 'n':
                strcpy(name, optarg);
                break;
            default:
                fprintf(stderr, "Usage : %s -n name -p port -m msg\n", argv[0]);
                exit(1);
        }
    }

    if (!strlen(name)) {
        //命令行参数没写，读取配置文件
        strcpy(name, read_conf(config, "name"));
    }
    if (!port) port = atoi(read_conf(config, "port"));
    if (!strlen(msg)) {
        strcpy(msg, read_conf(config, "msg"));
    }
    DBG(L_RED"name = %s\n"NONE, name);
    DBG(L_RED"port = %d\n"NONE, port);
    DBG(L_RED"msg = %s\n"NONE, msg);


    int listener;
    if ((listener = udp_socket_s(port)) < 0) {
        perror("udp_socket_s");
        exit(1);
    }
    DBG(L_BLUE"Starting...\n"NONE"listener %d ok!\n", listener);

    int epollfd, subfd;

    if ((epollfd = epoll_create(1)) < 0) {
        perror("epoll_create");
        exit(1);        
    }
    if ((subfd = epoll_create(1)) < 0) {
        perror("epoll_create");
        exit(1);        
    }

    struct epoll_event ev, events[MAX_N];

    ev.events = EPOLLIN;
    ev.data.fd = listener;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listener, &ev) < 0) {
        perror("epoll_ctl");
        exit(1);
    }
    
    pthread_t c_discover;
    pthread_create(&c_discover, NULL, client_discover, NULL);

    while (1) {
        int nfds = epoll_wait(epollfd, events, MAX_N, -1);
        if (nfds < 0) {
            perror("epoll_wait");
            exit(1);
        }
        DBG("receve data...\n");
        for (int i = 0; i < nfds; i++) {
            struct User newuser;
            int new_fd;
            if ((new_fd = udp_accept(listener, &newuser)) < 0) {
                fprintf(stderr, "error in upd_accent!\n");
                continue;
            }
            //添加到从反应堆
            add_to_reactor(subfd, &newuser);
        }
        DBG("receve data done!\n");
    }



    return 0;
}
