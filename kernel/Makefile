# Makefile kernel

CC=bcc
CFLAGS=-W -V -I -ansi

all : build

build : ../object/main.o ../object/kernel.o ../object/io.o ../object/sfs.o ../object/sector.o ../object/library.o ../object/syscall_handler.o ../object/util_asm.o ../object/interrupt.o ../object/disk_sector.o 

rebuild : clean build

../object/main.o : main.c
	$(CC) $(CFLAGS) -c $< -o $@

../object/kernel.o : kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

../object/io.o : io.c
	$(CC) $(CFLAGS) -c $< -o $@

../object/sfs.o : sfs.c 
	$(CC) $(CFLAGS) -c $< -o $@

../object/sector.o : sector.c
	$(CC) $(CFLAGS) -c $< -o $@

../object/library.o : library.c
	$(CC) $(CFLAGS) -c $< -o $@

../object/syscall_handler.o : syscall_handler.c
	$(CC) $(CFLAGS) -c $< -o $@

../object/util_asm.o : util_asm.s
	as86 $ $< -o $@

../object/interrupt.o : interrupt.s
	as86 $ $< -o $@

../object/disk_sector.o :  disk_sector.s
	as86 $ $< -o $@


clean :
	rm -rf ../object/*.o
	rm -rf *~
	
