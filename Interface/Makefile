# Makefile

CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS =
LDLIBS =

SRC = encoding.c decoding.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: encoding decoding

test: encoding.o decoding.o

-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} encoding decoding

# END

