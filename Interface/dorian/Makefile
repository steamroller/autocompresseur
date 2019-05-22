# simple SDL mini Makefile
CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD 
CFLAGS= -Wall -Wextra -std=c99 -O3 -g -Wno-stringop-overflow
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm


SRC= comp.c pixel_operations.c compressionimage.c display.c  
OBJ= ${SRC:*.c=.o}
SRC2= decompression.c pixel_operations.c display.c decomp.c
OBJ2=${SRC2:*.c=.o}

all: comp decomp 

comp: ${OBJ}

decomp:${OBJ2}


clean:
	${RM} comp comp.d decomp decomp.d *.o
	${RM} *.DCT *.tree
# END

