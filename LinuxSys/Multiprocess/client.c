
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <ctype.h>

#define SERV_PORT 5000
void sys_err(const char* str)
{
    perror(str);
    exit(1);
}
int main(int argc,char *argv[])
{
    int cfd;
    int ret,res;
    char buf[256];
    int count = 10;

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr.s_addr);


    cfd = socket(AF_INET,SOCK_STREAM,0);
    if(cfd == -1){
        sys_err("socket error");
    }


    ret = connect(cfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    if(ret == -1){
        sys_err("connect error");
    }

    while(--count){
        write(cfd,"hello\n",6);

        res = read(cfd,buf,sizeof(buf));

        write(STDOUT_FILENO,buf,res);
        sleep(1);
    }

    close(cfd);
    return 0;
}
