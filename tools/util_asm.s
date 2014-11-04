;util_asm.s
.global _init_syscalls
.global _syscall_handler
.global _printString
.extern _syscall_handler
; interrupt 0x80 vector (80 * 4 = 320)
; interrupts vectors start at address 0x0000:0x0000
; each vector uses 4 bytes (32-bit).
int80_addr equ (0x80 * 4)
; Set up the interrupt 0x80 vector used for system calls.
; When an interrupt 0x80 occurs, it calls _int80_stub below.
; void init_syscalls()

	
	
_init_syscalls:


	push bp
	mov bp,sp
	mov dx,#_int80_stub ; get the address of the interruption service routine (ISR)
	push ds
	push si
	mov ax,#0 ; interrupts vectors start at address 0x0000:0x0000
	mov ds,ax
	mov si,#int80_addr
	mov ax,cs ; have interrupt go to the current segment
	mov [si+2],ax
	mov [si],dx ; set up our vector
	pop si
	pop ds
	pop bp
	ret




; Stub routine called when an interrupt 0x80 occurs.
; This stub calls the syscall_handler function defined in the C code.
; void syscall_handler(uint syscall_nb, uint arg1, uint arg2, uint arg3, arg4)

_int80_stub:
	; arguments are pushed from right to left (i.e. ax = 1st argument)
	push di
	push dx
	push cx
	push bx
	push ax
	sti
	call _syscall_handler
	; The following pops are required but we don't care about their values.
	; We just avoid popping into ax since we need to keep
	; it unchanged as it stores the function's return value.
	pop bx
	pop bx
	pop bx
	pop bx
	pop bx
	iret ; pop ip, cs and flags registers (3 registe

;------------- display message function -------------;

printCharacter:			; Procedure to print character on screen
	mov ah, 0x0E		; Set registers to display a message
	mov bh, 0x00		
	mov bl, 0x07		
	int 0x10		; Call video interrupt
	ret			


_printString:			; Procedure to print string on screen

next_character:			
	mov al, [si]		; Store byte in AL
	inc si			; Increment SI
	or al, al		; Check if end of string
	jz exit_function 	; if end, return
	call printCharacter 	; else print char
	jmp next_character	; Get next char
exit_function:
	ret			


