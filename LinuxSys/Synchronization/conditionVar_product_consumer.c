#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

struct msg{
    int num;
    struct msg* next;
};

struct msg* head;

pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;//定义条件
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //定义互斥量 并初始化

/*=================================================*/





/*==================生产者===============================*/
void *product(void *p)
{
    while(1){
        struct msg* pp =(struct msg*) malloc(sizeof(struct msg));
        pp->num = rand() % 1000 +1; //生产者负责制作

        pthread_mutex_lock(&mutex); //制作完之后获取锁，将数据写入
        printf("--product===================%d\n",pp->num);
        pp->next = head;
        head = pp;
        pthread_mutex_unlock(&mutex); //写完立即释放锁

        pthread_cond_signal(&has_product);//通知其他阻塞的线程
        sleep(rand() % 5);
    }
    return NULL;
}

/*==================消费者================================*/
void *consumer(void *c)
{
    struct msg* cp;

    while(1){
        pthread_mutex_lock(&mutex);//尝试获取锁
        //if(head == NULL){  //当有多个线程时会导致段错误
        while(head == NULL){
            pthread_cond_wait(&has_product,&mutex); //没有资源的时候等待 解锁
        } //有资源了会加锁

        cp = head;
        head = head->next;
        pthread_mutex_unlock(&mutex);//获取完之后立即解锁  锁的粒度尽量小

        printf("--consumer--%lu====>>%d\n",pthread_self(),cp->num);
        free(cp);

        sleep(rand() % 3);
    }


    return NULL;
}



int main(void)
{
    srand(time(NULL));
    pthread_t cid , pid , cid2;
    int ret;


    //create 
    ret = pthread_create(&pid,NULL,product,NULL);
    if(ret != 0){
        fprintf(stderr,"pthread_creat error:%s\n",strerror(ret));
        exit(1);
    }
    ret = pthread_create(&cid,NULL,consumer,NULL);
    if(ret != 0){
        fprintf(stderr,"pthread_creat error:%s\n",strerror(ret));
        exit(1);
    }
    ret = pthread_create(&cid2,NULL,consumer,NULL);
    if(ret != 0){
        fprintf(stderr,"pthread_creat error:%s\n",strerror(ret));
        exit(1);
    }


    /*=================回收线程================================*/
    ret = pthread_join(cid,NULL);
    if(ret != 0){
        fprintf(stderr,"pthread_join error:%s\n",strerror(ret));
        exit(1);
    }
    ret = pthread_join(pid,NULL);
    if(ret != 0){
        fprintf(stderr,"pthread_join error:%s\n",strerror(ret));
        exit(1);
    }
    ret = pthread_join(cid2,NULL);
    if(ret != 0){
        fprintf(stderr,"pthread_join error:%s\n",strerror(ret));
        exit(1);
    }

    /*=================销毁锁和条件================================*/
    pthread_cond_destroy(&has_product);
    pthread_mutex_destroy(&mutex);

    pthread_exit((void*)0);
}
