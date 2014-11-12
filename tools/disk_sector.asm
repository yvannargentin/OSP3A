.global read_sector_raw

_read_sector_raw :
	push bp
	mov bp, sp
	
	mov ah, #0x42
	mov dx, [bp+4]
	mov si, [bp+6]
	mov bx, ds
	mov [si+6], bx	 ;fixup the segment
	int #0x13
	
	pop bp
	ret
