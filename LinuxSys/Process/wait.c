#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc , char *argv[])
{
    pid_t pid;
    pid_t wpid = 0;
    int status;
    pid = fork();
    if(pid == -1){
        perror("fork error");
        exit(1);
    } else if(pid == 0) {
        printf("===>I'll die after 10s,my pid = %d\n",getpid());
        sleep(10);
        printf("---child die\n");
        return 88;
    } else if(pid > 0){
        wpid = wait(&status);
        if(wpid == -1){
            perror("wait error");
            exit(1);
        }
        if(WIFEXITED(status)){
            printf("自己死亡 , exit id = %d\n",WEXITSTATUS(status));
        }
        if(WIFSIGNALED(status)){
            printf("被他杀=》sig id = %d\n",WTERMSIG(status));
        }
    }
    return 0;
}
