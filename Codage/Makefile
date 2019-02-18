# Makefile

CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS =
LDLIBS =

SRC = encryption.c decoding.c decoding_test.c encryption_test.c 
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: encryption encryption_test decoding decoding_test

encryption: encryption.o
encryption_test: encryption_test.o
decoding: decoding.o
decoding_test: decoding_test.o 

-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} encryption decoding encryption_test decoding_test

# END

