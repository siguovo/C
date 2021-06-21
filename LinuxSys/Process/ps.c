#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>

//ps aux > newfile 
int main(int argc , char *argv[])
{
    int fd;
    fd = open("ps.out",O_RDWR | O_CREAT | O_TRUNC ,0644);
    if(fd == -1){
        perror("open error");
        exit(1);
    }
    dup2(fd,STDOUT_FILENO);

    execlp("ps","ps","aux",NULL);
    perror("execlp error");

    //close(fd);
    return 0;
}
