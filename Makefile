qemu : image.img
	qemu-system-i386 -hda image.img

image.img : ./object/boot.bin ./object/main.o ./object/kernel.o  ./object/util_asm.o ./object/syscall_handler.o ./object/interrupt.o ./object/io.o ./object/sector.o 
	ld86 -M -m -d -s -o kernel.img ./object/main.o ./object/kernel.o  ./object/util_asm.o ./object/interrupt.o ./object/syscall_handler.o ./object/io.o ./object/sector.o 
	dd if=/dev/zero of=image.img bs=512 count=100 
	dd conv=notrunc seek=0 if=./object/boot.bin of=image.img 
	dd conv=notrunc seek=1 if=./kernel.img of=image.img 
	dd conv=notrunc seek=10 if=./fichier.txt of=image.img

./object/boot.bin : 
	nasm ./boot/bootloader.asm -f bin -o ./object/boot.bin

./object/util_asm.o : 
	as86 ./kernel/util_asm.s -o ./object/util_asm.o
	
./object/main.o : 
	bcc -W -V -I -ansi -c ./kernel/main.c -o ./object/main.o 

./object/kernel.o : 
	bcc -W -V -I -ansi -c ./kernel/kernel.c -o ./object/kernel.o

clean :
	rm -f ./object/*.o ./object/*.bin image.img kernel.img

./object/io.o:
	bcc -W -V -I -ansi -c ./kernel/io.c -o ./object/io.o

./object/sector.o:
	bcc -W -V -I -ansi -c ./kernel/sector.c -o ./object/sector.o

./object/syscall_handler.o : 
	bcc -W -V -I -ansi -c ./kernel/syscall_handler.c -o ./object/syscall_handler.o

./object/interrupt.o: 
	as86 ./kernel/interrupt.s -o ./object/interrupt.o
