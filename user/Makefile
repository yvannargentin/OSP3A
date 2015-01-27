# Makefile user

CC=bcc
CFLAGS=-W -V -I -ansi

all : build

build : shell.bin

rebuild : clean build

shell.bin : shell.c
	$(CC) $(CFLAGS) -c $< -o $@



clean :
	rm -rf *.o
	rm -rf *~
	
