;\file disk_sector.s
;\brief this file content the fonction in assembly who allow to set the DS and get the buffer

.global _sector_raw ; allow to use this fonction in c
;sector_raw(int ah, int interruption, packet p)
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
