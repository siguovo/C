#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>

// int main(int argc , char *argv[])
void sys_err(const char* str)
{
    perror(str);
    exit(1);
}

void fun()
{
    //return NULL;
    pthread_exit(NULL);
    return ;
}

void *tfn(void *arg)
{
    int i = (int)arg;
    sleep(i);
    if(i == 2){
        //return NULL;   //return 是返回到调用者
        //fun(); 
        //exit(0);        //退出当前的进程
        pthread_exit(NULL); //退出线程
        
    }
    printf("===>>I'm %dth thread:  pid = %d   tid = %lu\n",i+1,getpid(),pthread_self());
    return NULL;
}


int main(void)
{
    int i;
    int ret;
    pthread_t tid;

    for(i = 0; i < 5; i++){
        ret = pthread_create(&tid,NULL,tfn,(void *)i);
        if(ret != 0){
            sys_err("pthread_create error");
        } 
    }

    sleep(5);
    printf("$$$$$$$$$>>I'm Main:  pid = %d   tid = %lu\n",getpid(),pthread_self());
    return 0;
}
