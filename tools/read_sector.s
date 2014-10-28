;void read_sector(int sector, uchar *buf);
.global _read_sector

_read_sector:
; init the stack
push bp
mov bp,sp
push si

; read the sector 
mov ah, 0x02    ; Read Disk Sectors
mov al, 0x01	; number of sectors to read
mov ch, 0x00	; cylinder number
mov ax,[bp+4] 	; get the number sector
mov cl, ax		; sector number
mov dh, 0x00	; head number

; use the data buffer
mov ax, [bp+6]	; get the buffer
mov bx, ax
mov es, bx		; data buffer

int 0x13		; interruption 
ret
