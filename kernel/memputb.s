.global _memputb
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
