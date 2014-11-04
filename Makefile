qemu : image.img
	qemu-system-i386 -hda image.img

image.img : boot.bin kernel.o util_asm.o main.o
	ld86 -M -m -d -s -o kernel.img main.o kernel.o util_asm.o ./tools/io.o ./tools/syscall_handler.o ./tools/sector.o ./tools/interrupt.o
	dd if=/dev/zero of=image.img bs=512 count=100 
	dd conv=notrunc seek=0 if=./boot.bin of=image.img 
	dd conv=notrunc seek=1 if=./kernel.img of=image.img 

boot.bin : 
	nasm ./boot/bootloader.asm -f bin -o boot.bin

util_asm.o : 
	as86 ./kernel/util_asm.s -o util_asm.o
	
main.o : 
	bcc -W -V -I -ansi -c ./kernel/main.c -o main.o

kernel.o : 
	bcc -W -V -I -ansi -c ./kernel/kernel.c -o kernel.o

clean :
	rm -f boot.bin image.img kernel.o util_asm.o ./tools/io.o ./tools/sector.o ./tools/syscall_handler.o main.o tools/interrupt.o

precompile : 
	bcc -W -V -I -ansi -c ./tools/io.c -o ./tools/io.o
	bcc -W -V -I -ansi -c ./tools/sector.c -o ./tools/sector.o
	bcc -W -V -I -ansi -c ./tools/syscall_handler.c -o ./tools/syscall_handler.o
	as86 ./tools/interrupt.s -o tools/interrupt.o
