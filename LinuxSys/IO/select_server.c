#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <ctype.h>
#include <sys/select.h>
#include <sys/time.h>


#include "wrip.h"
#define SERV_PORT 5000


int main(void)
{
    int listenfd,clifd;
    int ret;
    struct sockaddr_in serv_addr,clie_addr;
    socklen_t clie_addr_len;
    char buf[BUFSIZ];

    listenfd = Socket(AF_INET,SOCK_STREAM,0);

    int opt = 1;
    ret = setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    if(ret == -1){
        perror("setsockopt error");
        exit(1);
    }

    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    Bind(listenfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));

    Listen(listenfd,128);

    fd_set rset,allset;
    FD_ZERO(&allset);
    FD_SET(listenfd,&allset);
    int maxi = listenfd;
    int i,j;
    //int select(int nfds, fd_set *readfds, fd_set *writefds,fd_set *exceptfds, struct timeval *timeout);
    while(1){
        rset = allset;
        ret = select(maxi+1,&rset,NULL,NULL,NULL);
        if(ret == -1){
            perr_exit("select error");
        } 
        if(FD_ISSET(listenfd,&rset)){
            clie_addr_len = sizeof(clie_addr);
            clifd = Accept(listenfd,(struct sockaddr*)&clie_addr,&clie_addr_len);
            FD_SET(clifd,&allset);
            if(clifd > maxi)
                maxi = clifd;
            if(ret == 1)
                continue;
        }
        for(i = listenfd+1;i <= maxi;i++){
            if(FD_ISSET(i,&rset)){
                ret = Read(i,buf,sizeof(buf));
                if(ret == 0){
                    Close(i);
                    FD_CLR(i,&allset);
                }
                for(j = 0; j < ret; j++){
                    buf[j] = toupper(buf[j]);
                }

                Write(i,buf,ret);

                Write(STDOUT_FILENO,buf,ret);
            }
        }
    }
    Close(listenfd);
    return 0;
}
