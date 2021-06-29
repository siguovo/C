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

void *tfn(void *arg)
{
    long retval = (long)arg + 10;
    printf("=======%ldth thread  pid = %d  tid = %lu\n",(long)arg+1,getpid(),pthread_self());
    return (void*)retval;
}


int main(void)
{
    long i;
    int ret;
    pthread_t tid[5];
    int* retval[5];

    //创建五个线程
    for(i = 0; i < 5; i++){
        ret = pthread_create(&tid[i],NULL,tfn,(void*)i);
        if(ret != 0){
            sys_err("pthread_create error");
        } 
    }

    //回收五个线程
    for(i = 0; i < 5; i++){
        ret = pthread_join(tid[i],(void**)&retval[i]); 
        if(ret != 0){
            sys_err("pthead_join error");
        }
        printf("jion %ldth thread  retval = %ld\n",i+1,(long)retval[i]);
    }

    pthread_exit(NULL);
}
