#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc,char *argv[])
{
    int i; 
    pid_t pid,wpid;
    //循环创建子进程
    for(i = 0;i < 5; i++){
        pid = fork();
        if(pid == 0){
            break;
        }
    }
    //阻塞回收子进程
    if( i== 5){
        while((wpid = waitpid(-1,NULL,WNOHANG)) != -1){
            if(wpid > 0){
                printf("wait child =======================> %d\n",wpid);
            } else if(wpid == 0) {
                sleep(1);
                continue;
            } 
        }
    } else {
        sleep(i);
        printf("I'm child %dth,pid = %d\n",i+1,getpid());
    }

    return 0;
}
