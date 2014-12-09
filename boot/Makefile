CC=bcc
CFLAGS=-W -V -I -ansi
LDFLAGS=-M -m -d -s


all : build

build :
	nasm bootloader.s -f bin -o ../object/boot.bin

rebuild : clean build

clean :
	rm -rf ../object/boot.bin
	
