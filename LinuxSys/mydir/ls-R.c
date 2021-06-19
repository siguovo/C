#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include <dirent.h>

void isFile(char* name);
//回调函数 
void read_dir(char *dir,void (*func)(char*))
{
    //保存文件路径长度（最长只能为256）
    char path[256];
    DIR* dp;
    struct dirent *sdp;
      dp = opendir(dir);
      if(dp == NULL){
        perror("opendir error");
        return;
    }
    while((sdp = readdir(dp)) != NULL){
        if(strcmp(sdp->d_name,".") == 0 || strcmp(sdp->d_name,"..") == 0)
        {
            continue;
        }
        if(strlen(dir) + strlen(sdp->d_name)+2 > sizeof(path)){
            fprintf(stderr,"read_dir: can't open %s\n ",dir);
        }else{
            sprintf(path,"%s/%s",dir,sdp->d_name);
            //isFile(path);
           (*func)(path);
        }
    }
}

void isFile(char* name)
{
    int ret = 0;
    struct stat sbuf;

    ret = stat(name,&sbuf);
    if(ret == -1){
        perror("stat error");
        return;
    }
    if(S_ISDIR(sbuf.st_mode)){
        read_dir(name,isFile);    
    }
    printf("%-25s\t%-8ld\n",name,sbuf.st_size);

    return; 
}


int main(int args,char *argv[])
{
  //判断传入的参数
  if(args == 1){
      isFile(".");
  }else{
      isFile(argv[1]);
  }
  return 0;
}
