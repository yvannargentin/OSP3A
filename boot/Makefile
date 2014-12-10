# Makefile boot 
OUT=../object/boot.bin

$(OUT): bootloader.s
	nasm -f bin $< -o $@

rebuild : clean build

clean :
	rm -rf ../object/boot.bin
	rm -rf *~
	
