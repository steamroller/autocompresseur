# simple SDL mini Makefile
CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD 
CFLAGS= -Wall -Wextra -O3 -g
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm


SRC= main.c pixel_operations.c compressionimage.c display.c  
OBJ= ${SRC:*.c=.o}

all: main 

main : ${OBJ} 

clean:
	${RM} main main.d *.o
	${RM} *.DCT *.tree
# END

