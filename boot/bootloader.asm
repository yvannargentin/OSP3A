; A simple real-mode boot loader

KERN_SEG        equ     0x1000  ; kernel loaded at this address
KERN_SIZE       equ     16      ; max kernel size in sectors (8KB)
KERN_START      equ     1       ; sector where kernel resides (0-indexed)
BOOT_DRIVE      equ     0x80    ; boot drive (0x00 = floppy, 0x80 = HDD)
STACK_OFFS      equ     0xfbfe  ; offset at which the stack starts

[BITS 16]
[ORG 0x0]

	; initialize segments 
	mov ax, KERN_SEG   ; data segment must be = code segment (tiny memory model!)
	mov ds, ax
	mov es, ax
	mov ss, ax

	; stack starts at KERN_SEG:STACK_OFFS (grows downward)
	mov ax, STACK_OFFS
	mov sp, ax

	; reset drive
	xor ax, ax
	int 0x13

	; display message
	push ds
	mov ax, 0x7c0 ; BIOS loads the 1st sector at 0x7c00
	mov ds, ax
	mov si, msg
	call print_string

	; load kernel at address KERN_SEG:0
	; uses BIOS extended read
	mov ah, 0x42
	mov dl, BOOT_DRIVE      ; set boot drive
	mov si, packet
	int 0x13
	pop ds

	; jump to kernel
	jmp KERN_SEG:0

; =============================================================================
; print string located whose address is at [si]
print_string:
	push ax
	push si
	mov ah, 0xe
print_string_loop:
	mov al, byte [si]
	cmp al, 0
	je print_string_done
	int 0x10
	inc si
	jmp print_string_loop
print_string_done:
	pop si
	pop ax
	ret

; =============================================================================
; data

; memory structure required by the extended read call
packet:
	size           db 0x10
	reserved       db 0
	sect_count     dw KERN_SIZE
	addr_offset    dw 0
	addr_segment   dw KERN_SEG
	first_sect     dq KERN_START ; first sector to read (0-indexed)

	msg db "Loading kernel...",13,10,0

	; fill with nop instructions until offset 510
	times 510-($-$$) db 0x90

	; last 2 bytes of sector: indicate a bootable sector
	dw 0xAA55
