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


    //select() 实现多路IO
    int i,j,maxfd;
    fd_set rset,allset;
    FD_ZERO(&allset);
    FD_SET(lfd,&allset);
    maxfd = lfd;

    while(1){
        rset = allset;
        ret = select(maxfd+1,&rset,NULL,NULL,NULL);
        if(ret < 0){
            perr_exit("select error");
        }

        if(FD_ISSET(lfd,&rset)){
            //4.accept() 文件描述符  客户端的地址(传出参数)  客户端地址的长度(传入传出参数)
            clie_addr_len = sizeof(clie_addr);
            cfd = Accept(lfd,(struct sockaddr*)&clie_addr,&clie_addr_len);
            FD_SET(cfd,&allset);

            if(maxfd < cfd)     //始终保持maxfd 是最大的文件描述符
                maxfd = cfd;
            if(ret == 1)        //如果为1 说明只有lfd  不用执行下面的代码了
                continue;
        }

        for(i = lfd+1; i <= maxfd; i++){
            if(FD_ISSET(i,&rset)){
                //5.read()  从客户端读数据，读到buf中，返回读到的大小
                ret = Read(i,buf,sizeof(buf));
                if(ret == 0){
                    Close(i);
                    FD_CLR(i,&allset);
                }
                //6.业务代码
                /*========================业务代码===================================*/
                for(j = 0; j < ret; j++)
                    buf[j] = toupper(buf[j]);
                /*========================业务代码===================================*/

                //7.write() 写回给客户端操作后的数据
                Write(i,buf,ret);
                Write(STDOUT_FILENO,buf,ret);
            }
        }
    }
    Close(lfd);
    return 0;
}
