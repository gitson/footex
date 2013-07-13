INCLUDES=$(wildcard *.h)
CC=gcc
CFLAGS=-I.
RM=rm
TARGETS=futex futex1

all: ${TARGETS}

futex: futex.o common.o
	$(CC) $^ -o $@

futex1: futex1.o common.o
	$(CC) $^ -o $@

%.o: %.c ${INCLUDES}
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) -f *.o ${TARGETS}
