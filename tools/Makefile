CC=gcc
CFLAGS=-c
LDFLAGS=-o

all: build

	$(CC) $(LDFLAGS) structure ./structure.c ./sfsadd.o ./sfsdel.o ./sfsls.o

build :
	$(CC) $(CFLAGS) ./sfsdel.c
	$(CC) $(CFLAGS) ./sfsadd.c
	$(CC) $(CFLAGS) ./sfsls.c

clean :
	rm ./*.o
