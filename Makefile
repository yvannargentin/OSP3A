# Makefile principal

LDFLAGS=-M -m -d -s

all : clean build disk.img qemu

build : mboot mkernel mtools muser

mboot :
	make -C boot

mkernel : 
	make -C kernel

mtools : 
	make run -C tools

muser : 
	make -C user
	

rebuild : clean build

disk.img :
	ld86 $(LDFLAGS) -o kernel.img ./object/main.o ./object/kernel.o ./object/util_asm.o ./object/interrupt.o ./object/disk_sector.o ./object/sfs.o ./object/library.o ./object/ass_exec.o ./object/exec.o ./object/syscall_handler.o ./object/io.o ./object/sector.o 
	dd if=/dev/zero of=image.img bs=512 count=1000
	dd conv=notrunc seek=0 if=./object/boot.bin of=image.img 
	dd conv=notrunc seek=1 if=./kernel.img of=image.img 
	dd conv=notrunc seek=20 if=./tools/fs.img of=image.img



qemu : image.img
	qemu-system-i386 -hda image.img

clean :
	rm -rf *.img
	rm -rf *~
	make clean -C kernel
	make clean -C boot
	make clean -C tools
	make clean -C user
	
