.global _interrupt
; int interrupt(int number, int ax, int bx, int cx, int dx, int
di)
_interrupt:
push bp
mov bp,sp
push si
mov ax,[bp+4] ; get the interrupt number in AL
push ds ; use self-modifying code to call the
right interrupt
mov bx,cs
mov ds,bx
mov si,#intr
mov [si+1],al ; change the 00 below to the contents of
AL
pop ds
mov ax,[bp+6] ; get the other parameters AX, BX, CX, DX
and DI
mov bx,[bp+8]
mov cx,[bp+10]
mov dx,[bp+12]
mov di,[bp+14]
pop si
pushf
intr: int #0x00 ; call interrupt (00 will be changed
above)
popf
pop bp
ret ; return AX implicit
