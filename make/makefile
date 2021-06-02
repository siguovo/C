#############################                                                                                                                                                                                     
#第一种方案:生成.o文件
TAR = test
OBJ = main.o add.o
CC := gcc 

$(TAR):$(OBJ)
    $(CC)  $^ -o $@

%.o:%.c
    $(CC) -c $^ -o $@


.PHONY:clean
cleanall:
    rm -rf $(OBJ) $(TAR) 
clean:
    rm -rf $(OBJ)

###############################
#第二种方案:不生成.o文件 直接生成可执行文件
TAR = mybin
OBJ = main.c add.c
CC = gcc


$(TAR):$(OBJ)
    $(CC) $^ -o $@

.PHONY:clean
clean:
    rm -rf $(TAR)

##############################
#第三种方案:不生成.o文件 直接生成可执行文件，多用.PHONY 不推荐使用，浪费时间 
.PHONY:mybin 
TAR = mybin
OBJ = main.c add.c
CC = gcc


$(TAR):$(OBJ)
    $(CC) $^ -o $@

.PHONY:clean
clean:
    rm -rf $(TAR)

##############################
#第四种方案:不生成.o文件 直接生成可执行文件，命令行不显示make命令 
TAR = mybin
OBJ = main.c add.c
CC = gcc


$(TAR):$(OBJ)
    $(CC) $^ -o $@

.PHONY:clean
clean:
    rm -rf $(TAR)
	
	
##############################
#第五种方案:生成.o文件 另一种方案
mybin:main.o add.o
    gcc $^ -o $@
%.o:%.c
    gcc -c $<

.PHONY:clean 
clean:
    rm -f *.o mybin 

##############################
#第六种方案:第五种方案的改进
TAR = mybin 
OBJ = main.o add.o

$(TAR):$(OBJ)
    gcc $^ -o $@
%.o:%.c
    gcc -c $<
    #gcc -c $^ -o $@  #两种写法

.PHONY:
cleanall:
    rm -rf *.o mybin                                                                                                                                                                                               
clean:
    rm -rf *.o

##############################
#第七种方案:第五种和第六种方案的结合,相对精简版
TAR = mybin 
OBJ = main.o add.o

$(TAR):$(OBJ)
    gcc $^ -o $@
%.o:%.c
    gcc -c $<

.PHONY:
clean: rm -rf *.o
cleanall:
    rm -rf *.o $(TAR) 

##############################
#第八种方案:调试版本(debug)   

TAR = mybin_d
OBJ = main.o add.o

$(TAR):$(OBJ)
    gcc $^ -o $@
%.o:%.c
    gcc -c $< -g   #.o ---> .c 时打上-g 得到 debug版本 

.PHONY:
clean: 
    rm -rf *.o
cleanall:
    rm -rf *.o $(TAR) 
        
##############################
#第九种方案:用户版本(release) 
                              
TAR = mybin_d
OBJ = main.o add.o

$(TAR):$(OBJ)
     gcc $^ -o $@
%.o:%.c
    gcc -c $<

.PHONY:
clean:
    rm -rf *.o
cleanall:
    rm -rf *.o $(TAR) 


