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
    printf("pthread: pid = %d  tid = %lu\n",getpid(),pthread_self());

    return NULL;
}



int main(void)
{
    pthread_t tid;

    int ret = pthread_create(&tid,NULL,tfn,NULL);
    if(ret != 0)
        sys_err("pthread_create error");

    printf("main: pid = %d  tid = %lu\n",getpid(),pthread_self());
    pthread_exit(NULL);
}
