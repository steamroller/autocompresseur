CC=gcc
CPPFLAGS= -MMD `pkg-config --cflags gtk+-3.0 sdl`-MMD
CFLAGS= -Wall -Wextra -Werror  -std=c99 -g
LDLIBS= `pkg-config  --libs  gtk+-3.0 sdl` -lSDL_image -lm -export-dynamic


SRC= autocompression.c huffman.c comp.c pixel_operations.c compressionimage.c display.c  decompression.c decomp.c
OBJ=${SRC:*.c=.o}

.PHONY:clean all
all: autocompression

hautenf : ${OBJ}

clean:

	${RM} autocompression *.o *.d userdatal userdatam

