src = $(wildcard *.c)
targets = $(patsubst %.c, %, $(src))

CC = gcc
CFLAGS = -Wall -g 
INC = ./include
SC = $(wildcard ./src/*.c )

all:$(targets)

$(targets):%:%.c
	$(CC) $< $(SC) -I$(INC) -o $@ $(CFLAGS)

.PHONY:clean all
clean:
	-rm -rf $(targets)