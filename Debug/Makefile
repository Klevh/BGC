#!/bin/makefile

OFILES=../BGC.o main.o
OREALFILES=main.o BGC.o
EXEC=debug

LDFLAGS=-g
CFLAGS=-Wall -Wextra -ansi -pedantic

CC=gcc

CLEAN=*.o ~*

all:$(EXEC)

$(EXEC):$(OFILES)
	$(CC) $(OREALFILES) -o $@ $(LDFLAGS)

%.o:%.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm $(CLEAN)
clear: clean

cleaner:
	rm $(EXEC) $(CLEAN)
