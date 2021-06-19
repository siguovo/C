src = $(wildcard *.c)
target = $(patsubst %.c, %, $(src))
CFLAGS = -Wall -g
ALL:$(target)

$(target):%:%.c
	gcc $< -o $@ $(CFLAGS)

.PHONY:clean ALL 

clean:
	rm -rf $(target)
