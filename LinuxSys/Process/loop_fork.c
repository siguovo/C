#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>



int main(int argc,char *argv[])
{
    int i;
    for(i = 0;i < 5;i++){
        if(fork() == 0){
            break;
        } 
    }
    if(i == 5){
        printf("---parent process, pid = %d\n",getpid());
    }else{
        printf("---child %dth,pid = %d\n",i+1,getpid());
    }
    sleep(1);
    return 0;
}

