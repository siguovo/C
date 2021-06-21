#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //fork.()


int main(int argc,char *argv[])
{
    pid_t rpid;
    printf("before fork --1--\n");
    printf("before fork --2--\n");
    printf("before fork --3--\n");
    printf("before fork --4--\n");
    
    rpid = fork();
    if(rpid == -1){
        perror("fork error\n");
        exit(1);
    }else if(rpid == 0){
        printf("---- child creat , my pid = %d, myparent pid = %d\n",getpid(),getppid());
    }else if(rpid != 0){
        printf("---- parent process , mychild pid = %d ,my pid = %d, myparent pid = %d\n",rpid,getpid(),getppid());
    }

    printf("==================end of file\n");
    sleep(1);
    return 0;
}
