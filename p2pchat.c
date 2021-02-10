/*************************************************************************
	> File Name: p2pchat.c
	> Author: shubulan
	> Mail: gaoyulong1996@163.com
	> Created Time: Wed 10 Feb 2021 01:44:13 PM CST
 ************************************************************************/

#include "myhead.h" 

char *config = "./chat.conf";
int port;
char name[20] = {0}, msg[512] = {0};

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
    char *p = read_conf(config, "name");
    strcpy(name, p);
    printf("name = %s\n", name);
    
    if (!strlen(name)) {
        //命令行参数没写，读取配置文件
        
    }



    return 0;
}
