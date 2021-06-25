#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <ctype.h>
#include "wrip.h"
#include <signal.h>
#include <strings.h>
#include <wait.h>

/*   //打印一下客户端的IP地址和端口号
     char clie_IP[1024];
     printf("client IP:%s  port:%d\n", 
     inet_ntop(AF_INET,&clie_addr.sin_addr.s_addr,clie_IP,sizeof(clie_IP)),
     ntohs(clie_addr.sin_port)); */



#define SERV_PORT 5000

void catch_child(int signo)
{
    while(waitpid(0,NULL,WNOHANG) > 0);
    return;   

}


int main(int argc,char *argv[])
{
    int lfd ,cfd;
    int ret;
    int i;
    char buf[BUFSIZ]; 
    pid_t pid;


    struct sockaddr_in serv_addr;
    bzero(&serv_addr,sizeof(serv_addr));    //置零
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 


    struct sockaddr_in clie_addr; 
    socklen_t clie_addr_len = sizeof(clie_addr);
    /*==========================================================================*/

    //1.sockte()
    lfd = Socket(AF_INET,SOCK_STREAM,0);

    //2.bind()  文件描述符  服务端地址绑定  服务端地址的大小
    Bind(lfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    //3.listen() 文件描述符  所能监听的最大端口数 
    Listen(lfd,128);



    while(1){
        //4.accept() 文件描述符  客户端的地址(传出参数)  客户端地址的长度(传入传出参数)
        cfd = Accept(lfd,(struct sockaddr*)&clie_addr,&clie_addr_len);
        pid = fork();
        if(pid < 0){
            perr_exit("fork error");
        } else if(pid == 0){
            Close(lfd);
            break;
        } else {
            //注册信号量
            struct sigaction act;
            act.sa_handler = catch_child;
            sigemptyset(&act.sa_mask);
            act.sa_flags = 0;

            ret = sigaction(SIGCHLD,&act,NULL);
            if(ret == -1){
                perr_exit("sigaction error");
            }
            Close(cfd);
            continue;
        }
    }

    if(pid == 0){
        for(;;){
            //5.read()  从客户端读数据，读到buf中，返回读到的大小
            ret = Read(cfd,buf,sizeof(buf));
            if(ret == 0){
                Close(cfd);
                exit(1);
            }
            //6.业务代码
            /*========================业务代码===================================*/
            for(i = 0; i < ret; i++)
                buf[i] = toupper(buf[i]);
            /*========================业务代码===================================*/

            //7.write() 写回给客户端操作后的数据
            Write(cfd,buf,ret);
            Write(STDOUT_FILENO,buf,ret);
        }
    }
    return 0;
}
