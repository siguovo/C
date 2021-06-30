src = $(wildcard *.c)
INCLUDE = -levent 
target = $(patsubst %.c, %, $(src))
CFLAGS = -Wall -g

ALL:$(target)

$(target):%:%.c
	gcc $< -o $@ $(CFLAGS) $(INCLUDE)

.PHONY:clean ALL 

clean:
	rm -rf $(target)
