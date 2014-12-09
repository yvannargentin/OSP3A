CC=bcc
CFLAGS=-W -V -I -ansi
LDFLAGS=-M -m -d -s


all : clean build disk.img qemu

build :
	make run -C tools
	nasm ./boot/bootloader.s -f bin -o ./object/boot.bin

	$(CC) $(CFLAGS) -c ./kernel/main.c -o ./object/main.o
	$(CC) $(CFLAGS) -c ./kernel/kernel.c -o ./object/kernel.o
	$(CC) $(CFLAGS) -c ./kernel/io.c -o ./object/io.o
	$(CC) $(CFLAGS) -c ./kernel/sfs.c -o ./object/sfs.o
	$(CC) $(CFLAGS) -c ./kernel/sector.c -o ./object/sector.o
	$(CC) $(CFLAGS) -c ./kernel/syscall_handler.c -o ./object/syscall_handler.o
	
	as86 ./kernel/util_asm.s -o ./object/util_asm.o
	as86 ./kernel/interrupt.s -o ./object/interrupt.o
	as86 ./kernel/disk_sector.s -o ./object/disk_sector.o

rebuild : clean build

disk.img :
	ld86 $(LDFLAGS) -o kernel.img ./object/main.o ./object/kernel.o ./object/sfs.o ./object/util_asm.o ./object/interrupt.o ./object/disk_sector.o ./object/syscall_handler.o ./object/io.o ./object/sector.o 
	dd if=/dev/zero of=image.img bs=512 count=100 
	dd conv=notrunc seek=0 if=./object/boot.bin of=image.img 
	dd conv=notrunc seek=1 if=./kernel.img of=image.img 
	dd conv=notrunc seek=20 if=./tools/fs.img of=image.img



qemu : image.img
	qemu-system-i386 -hda image.img

clean :
	rm -rf *.o *.img
	
