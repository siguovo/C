CC = gcc
INCLUDE = -I./inc 
CFLAGS = -Wall -g
src = $(wildcard ./src/*.c) 
obj = $(patsubst ./src/%.c, ./obj/%.o, $(src))

ALL:a.out

a.out:$(obj)
	$(CC) $^ -o $@ $(CFLAGS)

$(obj):./obj/%.o:./src/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

clean:
	rm -rf $(obj) a.out

.PHONY:clean ALL 

