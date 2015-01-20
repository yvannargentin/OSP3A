# Makefile user

CC=bcc
CFLAGS=-W -V -I -ansi

all : build

build : helloworld.bin

rebuild : clean build

helloworld.bin : helloworld.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf *.o
	rm -rf *~
	
