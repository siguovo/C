#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>

int Var1 = 100;
int Var2 = 200;
pthread_mutex_t mutex;
pthread_mutex_t mutex2;

void *tfn1(void *arg)
{
    long id = (long)arg;

    while(1){
        pthread_mutex_lock(&mutex);//先尝试获取第一把锁
        
        Var1 += 10;
        printf("%ld号线程获取了第一把锁，修改数据Var1 = %d\n",id,Var1);
        sleep(2);
        
        pthread_mutex_lock(&mutex2);//再尝试获取第二把锁
        
        Var2 += 20;
        printf("%ld号线程获取了第二把锁，修改数据Var2 = %d\n",id,Var2);
        
        pthread_mutex_unlock(&mutex);
        pthread_mutex_unlock(&mutex2);
        sleep(1);

    }
    return NULL;
}


void *tfn2(void *arg)
{
    long id = (long)arg;

    while(1){
        pthread_mutex_lock(&mutex2);//先尝试获取第二把锁
        Var2 += 200;
        printf("%ld号线程获取了第二把锁，修改数据Var2 = %d\n",id,Var2);
        sleep(2);

        pthread_mutex_lock(&mutex);//再尝试获取第一把锁
        Var1 += 100;
        printf("%ld号线程获取了第一把锁，修改数据Var1 = %d\n",id,Var1);

        
        pthread_mutex_unlock(&mutex2);
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
}

int main(void)
{
    int ret;
    /*==============================初始化锁=======================================*/
    ret = pthread_mutex_init(&mutex,NULL);       
    if(ret != 0){
        fprintf(stderr,"phtread_mutex_init1 error:%s\n",strerror(ret));
        exit(1);
    }
    ret = pthread_mutex_init(&mutex2,NULL);     
    if(ret != 0){
        fprintf(stderr,"phtread_mutex_init2 error:%s\n",strerror(ret));
        exit(1);
    }





    /*==============================创建线程=======================================*/
    pthread_t tid,tid2;
    //线程1
    ret = pthread_create(&tid,NULL,tfn1,(void*)1);
    if(ret != 0){
        fprintf(stderr,"phtread_create error:%s\n",strerror(ret));
        exit(1);
    }
    //线程2
    ret = pthread_create(&tid2,NULL,tfn2,(void*)2);
    if(ret != 0){
        fprintf(stderr,"phtread_create error:%s\n",strerror(ret));
        exit(1);
    }



    /*==============================回收线程=======================================*/
    ret = pthread_join(tid,NULL);
    if(ret != 0){
        fprintf(stderr,"phtread_join error:%s\n",strerror(ret));
        exit(1);
    }
    ret = pthread_join(tid2,NULL);
    if(ret != 0){
        fprintf(stderr,"phtread_join error:%s\n",strerror(ret));
        exit(1);
    }
    

    /*==============================执行结束销毁锁=======================================*/
    ret = pthread_mutex_destroy(&mutex);           
    if(ret != 0){
        fprintf(stderr,"phtread_mutex_destroy1 error:%s\n",strerror(ret));
        exit(1);
    }
    ret = pthread_mutex_destroy(&mutex2);         
    if(ret != 0){
        fprintf(stderr,"phtread_mutex_destroy2 error:%s\n",strerror(ret));
        exit(1);
    }
    return 0;
}
