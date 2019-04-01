CC=gcc
CPPFLAGS= -MMD `pkg-config --cflags gtk+-3.0`
CFLAGS= -Wall -Wextra -Werror  -std=c99 -g
LDLIBS= `pkg-config  --libs  gtk+-3.0  ` -lm -export-dynamic


SRC= gui.c huffman.c
OBJ=${SRC:*.c=.o}

.PHONY:clean all
all: gui

hautenf : ${OBJ}

clean:

	${RM} gui *.o *.d userdatal userdatam

