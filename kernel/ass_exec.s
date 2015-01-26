STACK_OFFS equ 0xfbfe ; offset at which the stack starts
.global _jump
.global _memputb
.global _exit

;------------------------------------------------------------------------------
; Jump and start executing the code at the specified segment and offset 0.
; void jump(uint segment)
_jump:
	push bp
	mov bp,sp
	mov bx,[bp+4]; get the segment to jump to into bx
	push ds; save ds as it will be modified belowmov
	push si
	
	mov ax,cs ; modify the jmp below to jump to the specified segment
	mov ds,ax ; this is self-modifying code
	mov si,#jump
	mov [si+3],bx; change the first 0000 to the segment
	pop si
	
	pop ax; save segment of the caller in ax (= ds which was pushed above)
	mov cx,sp; save stack pointer
	mov dx,bp; save base pointer
	mov ds,bx; set up the segment registers to the specified segment
	mov ss,bx
	mov es,bx
	
	mov sp,#STACK_OFFS; set up the stack pointer
	mov bp,#STACK_OFFS
	
	; push sp, bp and current segment in order to resume
	; the execution context when returning from the call
	push cx; sp
	
	push dx; bp
	
	push ax; ds
	
	; far call (push both cs and ip on the stack)
jump: call #0x0000:0x0000
	; start running (the first 0000 is changed above)
	; restore ds, bp and sp into ax, bx and cx
	pop ax ;ds
	pop bx ;bp
	pop cx ;sp
	
	; restore the caller's context (segments, bp and sp)
	mov ds,ax
	mov es,ax
	mov ss,ax
	mov bp,bx
	mov sp,cx
	pop bp
ret


;------------------------------------------------------------------------------
; Write a byte at the specified segment:offset address.
; memputb(uint segment, uint offset, uchar byte)
_memputb:
	push bp
	mov bp,sp
	push es
	push di
	mov ax,[bp+4]
	mov es,ax
	mov di,[bp+6]
	mov ax,[bp+8]
	seg es
	mov byte [di],al
	pop di
	pop es
	pop bp
ret

;------------------------------------------------------------------------------
; exit and get back to the parent process (provided there is one)
_exit:
	; pop what is pushed by the compiler at the beginning of the program's main() function
	; required because when exit() is called the code never reaches the end of the main() function
	pop ax ; cancel the push si
	pop ax ; cancel the push di
	pop ax ; cancel the push bp
	; pop the ip from the call to exit()
	pop ax ; cancel implicit push ip (call exit)
retf ; return from a far call
