CC=bcc
CFLAGS=-W -V -I -ansi
LDFLAGS=-M -m -d -s


all : build

build :
	$(CC) $(CFLAGS) -c main.c -o ../object/main.o
	$(CC) $(CFLAGS) -c kernel.c -o ../object/kernel.o
	$(CC) $(CFLAGS) -c io.c -o ../object/io.o
	$(CC) $(CFLAGS) -c sfs.c -o ../object/sfs.o
	$(CC) $(CFLAGS) -c sector.c -o ../object/sector.o
	$(CC) $(CFLAGS) -c remove_file.c -o ../object/remove_file.o
	$(CC) $(CFLAGS) -c read_file.c -o ../object/read_file.o
	$(CC) $(CFLAGS) -c syscall_handler.c -o ../object/syscall_handler.o
		
	
	as86 util_asm.s -o ../object/util_asm.o
	as86 interrupt.s -o ../object/interrupt.o
	as86 disk_sector.s -o ../object/disk_sector.o

rebuild : clean build

clean :
	rm -rf ../object/*.o
	
