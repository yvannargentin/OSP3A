.global _sector_raw

_sector_raw:
	push bp
	mov bp, sp

	mov ah, [bp+4]
	mov dx, [bp+6]  ; adresse interruption 80
	mov si, [bp+8]	; adresse packet
	mov bx, ds
	mov [si+6], bx	 ;fixup the segment
	int #0x13
	
	pop bp
	ret
