qemu : image.img
	qemu-system-i386 -hda image.img

image.img : boot.bin kernel.o util_asm.o main.o
	ld86 -M -m -d -s -o kernel.img main.o kernel.o util_asm.o
	dd if=/dev/zero of=image.img bs=512 count=100 
	dd conv=notrunc seek=0 if=./boot.bin of=image.img 
	dd conv=notrunc seek=1 if=./kernel.img of=image.img 

boot.bin : 
	nasm ./boot/bootloader.asm -f bin -o boot.bin

util_asm.o : 
	as86 ./kernel/util_asm.s -o ./kernel/util_asm.o
	
main.o : 
	bcc -W -V -I -ansi -c ./kernel/main.c

kernel.o : 
	bcc -W -V -I -ansi -c ./kernel/kernel.c

clean :
	rm -f boot.bin image.img kernel.o util_asm.o
