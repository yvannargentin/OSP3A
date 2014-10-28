.global _print_string

;void print_string(char *str);
_print_string:

push bp
mov bp,sp

mov si, sp ;Store string pointer to SI
call printString	;call print string procedure

printCharacter:	; Procedure to print character on screen
mov ah, 0x0E	; Set registers to display a message
mov bh, 0x00	
mov bl, 0x07	
int 0x10	; call video interrupt
ret	

printString:	; Procedure to print string on screen

next_character:	
mov al, [si]	; Store byte in AL
inc si	; Increment SI
or al, al	; Check if end of string
jz exit_function ; if end, return
call printCharacter ; else print char
jmp next_character	; Get next char

exit_function:

ret




