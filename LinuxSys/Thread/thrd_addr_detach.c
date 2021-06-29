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
    pthread_attr_t attr;
    /*----------------------------------------------------------------*/
    //初始化线程状态
    int ret = pthread_attr_init(&attr);
    if(ret != 0){
        fprintf(stderr,"attr_init error:%s\n",strerror(ret));
        exit(1);
    }

    //设置线程的状态为 分离状态
    ret = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    if(ret != 0){
        fprintf(stderr,"attr_setdetachstate error:%s\n",strerror(ret));
        exit(1);
    }

    //创建子进程
    ret = pthread_create(&tid,&attr,tfn,NULL);
    if(ret != 0){
        fprintf(stderr,"pthread_create error:%s\n",strerror(ret));
        exit(1);
    }

    //销毁分离属性
    ret = pthread_attr_destroy(&attr);
    if(ret != 0){
        fprintf(stderr,"attr_estroy error:%s\n",strerror(ret));
        exit(1);
    }
    /*----------------------------------------------------------------*/


    //检查一下子线程是否已经分离
    ret = pthread_join(tid,NULL);
    if(ret != 0){
        fprintf(stderr,"pthread_join error:%s\n",strerror(ret));
        printf("thread success detached $$$$$$\n");
        exit(1);
    }



    printf("main : pid = %d   tid = %lu\n", getpid(),pthread_self());
    pthread_exit(NULL);
}
