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
#include <sys/epoll.h>


/*   //打印一下客户端的IP地址和端口号
     char clie_IP[1024];
     printf("client IP:%s  port:%d\n", 
     inet_ntop(AF_INET,&clie_addr.sin_addr.s_addr,clie_IP,sizeof(clie_IP)),
     ntohs(clie_addr.sin_port)); */


#define OPEN_SIZE 6000
#define SERV_PORT 5000


int main(int argc,char *argv[])
{
    int lfd ,cfd;
    char buf[BUFSIZ]; 
    int ret;


    struct sockaddr_in serv_addr;
    struct sockaddr_in clie_addr;           //accept() 接收客户端连接后接收客户端地址
    socklen_t clie_addr_len;
    /*==========================================================================*/



    //1.sockte()
    lfd = Socket(AF_INET,SOCK_STREAM,0);

    /*==============设置端口复用============================================================*/
    int opt = 1;
    ret = setsockopt(lfd,SOL_SOCKET,SO_REUSEADDR,(void*)&opt,sizeof(opt));
    if(ret == -1){
        perr_exit("setsockopt error");
    }
    /*=====================================================================================*/

    //2.bind()  文件描述符  服务端地址绑定  服务端地址的大小
    bzero(&serv_addr,sizeof(serv_addr));    //置零 bind()绑定端口
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    Bind(lfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    //3.listen() 文件描述符  所能监听的最大端口数 
    Listen(lfd,128);


    //epoll() 实现多路io 
    int efd;
    int maxi,i,j;
    struct epoll_event tep,ep[OPEN_SIZE];

    efd = epoll_create(OPEN_SIZE);  //创建监听红黑树
    if(efd == -1)
        perr_exit("epoll_create error");

    tep.events = EPOLLIN;   //将lfd 封装到结构体中
    tep.data.fd = lfd;

    ret = epoll_ctl(efd,EPOLL_CTL_ADD,lfd,&tep); //将lfd 的结构体挂上监听红黑树
    if(ret == -1)
        perr_exit("epoll_ctl error");

    while(1){
        // epoll_wait() 是server 的阻塞监听 
        // efd监听红黑树  ep 为struct epoll_event 类型数组  OPEN_SIZE 为数组的大小 -1 代表永久阻塞
        maxi = epoll_wait(efd,ep,OPEN_SIZE,-1);//返回值是发生事件的文件描述符总个数
        if(maxi == -1)
            perr_exit("epoll_wait error");

        for(i = 0; i < maxi; i++){
            int sockfd = ep[i].data.fd;

            if(sockfd == lfd){
                //4.accept() 文件描述符  客户端的地址(传出参数)  客户端地址的长度(传入传出参数)
                clie_addr_len = sizeof(clie_addr);
                cfd = Accept(lfd,(struct sockaddr*)&clie_addr,&clie_addr_len);

                tep.events = EPOLLIN;
                tep.data.fd = cfd;

                ret = epoll_ctl(efd,EPOLL_CTL_ADD,cfd,&tep);
                if(ret == -1)
                    perr_exit("epoll_ctl error");
            } else {
                //5.read()  从客户端读数据，读到buf中，返回读到的大小
                ret = Read(sockfd,buf,sizeof(buf));
                if(ret == 0){
                    //读到0 说明该客户端断开连接 将其从监听红黑树摘下
                    ret = epoll_ctl(efd,EPOLL_CTL_DEL,sockfd,NULL); 
                    if(ret == -1)
                        perr_exit("epoll_ctl error");
                    Close(sockfd);
                } else {
                    //6.业务代码
                    /*========================业务代码===================================*/
                    for(j = 0; j < ret; j++)
                        buf[j] = toupper(buf[j]);
                    /*========================业务代码===================================*/

                    //7.write() 写回给客户端操作后的数据
                    Write(sockfd,buf,ret);
                    Write(STDOUT_FILENO,buf,ret);
                }
            }
        }
    }
    Close(lfd);
    return 0;
}
