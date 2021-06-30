#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <event2/event.h>
#include <fcntl.h>


void read_cb(evutil_socket_t fd, short what,void* arg)
{
    char buf[BUFSIZ];
    int len = read(fd,buf,sizeof(buf));
    if(len == -1){
        perror("read error");
        exit(1);
    }

    printf("what : %s  read : %s\n",what & EV_READ ? "read Yes":"read No",buf);

    sleep(2);
    return;
}


int main()
{
    //fifo
    unlink("myfifo");
    mkfifo("myfifo",0644);
    //open 
    int fd = open("myfifo",O_RDONLY | O_NONBLOCK);
    if(fd == -1){
        perror("open error");
        exit(1);
    }
    //创建base
    struct event_base* base = event_base_new();

    //创建ev 事件对象
    struct event *ev = event_new(base,fd,EV_READ | EV_PERSIST,read_cb,NULL);

    //添加事件到event_base 
    event_add(ev,NULL);

    //循环
    event_base_dispatch(base);


    event_base_free(base);
    return 0;
}
