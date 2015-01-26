# Makefile tools

CC=gcc
CFLAGS=-c


all: build
	$(CC) -o structure ./main.c ./sfscreate.o ./sfsadd.o ./sfsdel.o ./sfsls.o

build : test.o test.bin
	$(CC) $(CFLAGS) ./sfsdel.c
	$(CC) $(CFLAGS) ./sfsadd.c
	$(CC) $(CFLAGS) ./sfsls.c
	$(CC) $(CFLAGS) ./sfscreate.c

test.o : test.c
	$(CC) $(CFLAGS) $<

test.bin : test.c
	$(CC) $(CFLAGS)  $< -o $@

.PHONY: run
run: all
	./structure

clean :
	rm -rf *.o structure 
	rm -rf *~
	
