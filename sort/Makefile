INCLUDES=$(wildcard *.h)
CC=gcc
CFLAGS=-I.
RM=rm
TARGETS=sort sort1

all: ${TARGETS}

sort: sort.o common.o
	$(CC) $^ -o $@

sort1: sort1.o common.o
	$(CC) $^ -o $@

%.o: %.c ${INCLUDES}
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) -f *.o ${TARGETS}
