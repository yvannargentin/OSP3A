qemu : image.img
	qemu-system-i386 -hda image.img

image.img : boot.bin kernel.bin
	dd if=/dev/zero of=image.img bs=512 count=100 
	dd conv=notrunc seek=0 if=./boot.bin of=image.img 
	dd conv=notrunc seek=1 if=./kernel.bin of=image.img 

boot.bin : ./boot/bootloader.asm
	nasm ./boot/bootloader.asm -f bin -o boot.bin

kernel.bin : ./kernel/kernel.asm
	nasm ./kernel/kernel.asm -f bin -o kernel.bin
	
clean :
	rm -f boot.bin image.img kernel.bin
