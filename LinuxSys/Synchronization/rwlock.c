#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>

int count;
pthread_mutex_t mutex;


void *tfn(void *arg)
{
    srand(time(NULL));
    while(1){
        pthread_mutex_lock(&mutex);
        printf("hello ");
        sleep(rand()%3);
        printf("world\n");
        pthread_mutex_unlock(&mutex);
        sleep(rand()%3);
    }
    return NULL;
}



int main(void)
{
    srand(time(NULL));
    pthread_t tid;
    int ret;
    ret = pthread_mutex_init(&mutex,NULL);            //初始化锁
    if(ret != 0){
        fprintf(stderr,"phtread_mutex_init error:%s\n",strerror(ret));
        exit(1);
    }

    ret = pthread_create(&tid,NULL,tfn,NULL);
    if(ret != 0){
        fprintf(stderr,"phtread_create error:%s\n",strerror(ret));
        exit(1);
    }


    while(1){
        pthread_mutex_lock(&mutex);     //想要打印前，先获取锁
        printf("HELLO ");
        sleep(rand()%3);
        printf("WORLD\n");
        //所有任务执行完成后，要释放锁 ,注意要在sleep前释放锁,表示是自己自愿释放的，而不是被CPU剥夺
        pthread_mutex_unlock(&mutex);  
        sleep(rand()%3);
    }

    ret = pthread_join(tid,NULL);
    if(ret != 0){
        fprintf(stderr,"phtread_join error:%s\n",strerror(ret));
        exit(1);
    }
    
    ret = pthread_mutex_destroy(&mutex);            //用完后销毁锁
    if(ret != 0){
        fprintf(stderr,"phtread_mutex_destroy error:%s\n",strerror(ret));
        exit(1);
    }
    return 0;
}
