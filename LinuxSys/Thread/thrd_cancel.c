#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>

// int main(int argc , char *argv[])

void *tfn(void *arg)
{
    while(1){
        printf("==============pthread: pid = %d  tid = %lu\n",getpid(),pthread_self());
        sleep(1);
    }
    return NULL;
}



int main(void)
{
    pthread_t tid;

    //创建子进程
    int ret = pthread_create(&tid,NULL,tfn,NULL);
    if(ret != 0){
        fprintf(stderr,"pthread_create error:%s\n",strerror(ret));
        exit(1);
    }
    printf("main: pid = %d  tid = %lu\n",getpid(),pthread_self());

    sleep(5);
    //杀死子进程
    ret = pthread_cancel(tid);
    if(ret != 0){
        fprintf(stderr,"pthread_cancel error:%s\n",strerror(ret));
        exit(1);
    }

    while(1);
    pthread_exit(NULL);
}
