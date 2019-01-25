CC=gcc
CPPFLAGS= -MMD `pkg-config --cflags gtk+-3.0`
CFLAGS= -Wall -Wextra -Werror -std=c99 -g
LDLIBS= `pkg-config  --libs  gtk+-3.0  ` -lm -export-dynamic


SRC= hautenf.c
OBJ=${SRC:*.c=.o}

.PHONY:clean all
all: hautenf

hautenf : ${OBJ}

clean:

	${RM} hautenf *.o

