#第一层:显示规则
#目标文件:依赖文件
hello:hello.o
	gcc hello.o -o hello
hello.o:hello.S
	gcc -c hello.S -o hello.o
hello.S:hello.i
	gcc -S hello.i -o hello.S
hello.i:hello.c

.PHONY:
clearall:
	rm -rf hello.o hello.S hello.i hello
clear:
	rm -rf hello.o hello.S hello.i
	
	
	
	
# =  +=  :=
#$ 
#%.c
#*.c


#  $^  所有依赖文件
#  $@  所有目标文件
#  $*  $+   $<   $?

