CC=bcc
CFLAGS=-W -V -I -ansi
LDFLAGS=-M -m -d -s


all : build disk.img qemu

build : 
	make -C boot
	make -C kernel
	make run -C tools

boot :
	make -C boot

kernel : 
	make -C kernel

tools : 
	make run -C tools
	

rebuild : clean build

disk.img :
	ld86 $(LDFLAGS) -o kernel.img ./object/main.o ./object/kernel.o ./object/util_asm.o ./object/interrupt.o ./object/disk_sector.o ./object/sfs.o ./object/read_file.o ./object/remove_file.o ./object/syscall_handler.o ./object/io.o ./object/sector.o ./object/intTostr.o
	dd if=/dev/zero of=image.img bs=512 count=100 
	dd conv=notrunc seek=0 if=./object/boot.bin of=image.img 
	dd conv=notrunc seek=1 if=./kernel.img of=image.img 
	dd conv=notrunc seek=20 if=./tools/fs.img of=image.img



qemu : image.img
	qemu-system-i386 -hda image.img

clean :
	rm -rf *.img
	make clean -C kernel
	make clean -C boot
	make clean -C tools
	
