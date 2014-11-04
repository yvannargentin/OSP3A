[BITS 16]
[ORG 0x0]
	
	; initialize segments
	mov ax, 0x7c0
	mov ds, ax
	
	; setup stack
	
	mov ss, ax
	mov sp, 0xffff

	; reset drive


;------------- 

	mov si, data 			;Store string pointer to SI
	call printString		;Call print string procedure
	jmp kernelLoader 		;


;------------- display message function -------------;

printCharacter:			; Procedure to print character on screen
	mov ah, 0x0E		; Set registers to display a message
	mov bh, 0x00		
	mov bl, 0x07		
	int 0x10		; Call video interrupt
	ret			


printString:			; Procedure to print string on screen

next_character:			
	mov al, [si]		; Store byte in AL
	inc si			; Increment SI
	or al, al		; Check if end of string
	jz exit_function 	; if end, return
	call printCharacter 	; else print char
	jmp next_character	; Get next char
exit_function:
	ret			


;------------- Load the kernel -------------;

kernelLoader:
	; Set registers to read sectors from a disk
        mov ah, 0x02    ; Read Disk Sectors
        mov al, 0x01    ; Nb sectors to read
        mov ch, 0x00    ; Track
        mov cl, 0x02    ; Sector
        mov dh, 0x00    ; Head

        mov bx, 0x1000  ; Set Segment to 0x1000 (futur kernel address)
        mov es, bx      ; 
	mov ds, bx	; Set data segment to 0x1000
        mov bx, 0x0000  ; Offset value

readsector:
        int 0x13        ; BIOS interruption
        jc readsector  	; if error retry

	mov ax, 0x1000
	mov ds, ax

        jmp 0x1000:0x0000      ; Jump to the kernel




	;Data
	data db 'Loading kernel at adress 0x1000', 10, 13, 0	

	; fill with nop instructions until offset 510
	times 510-($-$$) db 0x90

	; last 2 bytes of sector: indicate a bootable sector
	dw 0xAA55

