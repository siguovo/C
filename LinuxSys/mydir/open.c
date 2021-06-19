#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>



int main(int argc,char* argv[])
{ 
    int fd;
    fd = open("./ddc.c",O_RDONLY | O_CREAT | O_TRUNC ,0644);
    //fd = open("./test.c",O_RDONLY);
    printf("%d\n",fd);
    close(fd);
    return 0;
}
