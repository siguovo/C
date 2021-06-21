#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //fork.()


int main(int argc,char *argv[])
{
    pid_t rpid;
    
    rpid = fork();
    if(rpid == -1){
        perror("fork error\n");
        exit(1);
    }else if(rpid == 0){
        //ececlp("ls","ls","-l",NULL);
        //execl("./a.out","a.out",NULL);
        //execl("/bin/ls","ls","-l",NULL);
        char *argv[] = {"ls","-l",NULL};
        execvp("ls",argv);

        perror("execl error");
        exit(1);
    }else if(rpid != 0){
        sleep(1);
        printf("---parent process, pid = %d\n",getpid());
    }
    return 0;
}
