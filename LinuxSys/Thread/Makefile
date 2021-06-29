src = $(wildcard *.c)
target = $(patsubst %.c, %, $(src))
CFLAGS = -Wall -g
LIBS = -lpthread

ALL:$(target)

$(target):%:%.c
	gcc $< -o $@ $(CFLAGS) $(LIBS)

.PHONY:clean ALL 

clean:
	rm -rf $(target)
