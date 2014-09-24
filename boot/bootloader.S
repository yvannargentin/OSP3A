#YOLO SWAGG YVANN

A_CONSTANT	equ	0x100

[BITS 16]
[ORG 0x0]

	; initialize segments
	; ...

	; setup stack
	; ...

	; reset drive
	; ...

	; display message
	; ...

	; load kernel
	; ...

	; execute kernel
	; ...


	msg db "A message...",13,10,0

	; fill with nop instructions until offset 510
	times 510-($-$$) db 0x90

	; last 2 bytes of sector: indicate a bootable sector
	dw 0xAA55