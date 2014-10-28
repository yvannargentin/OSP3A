.global _read_string

;void read_string(char *buf);
_read_string:

push bp
mov bp,sp

; For each string already padded with 13, 10, $
; at the end, use the following:
mov ah, 08h
mov edi, sp
mov ecx, 16*8
cld

while:
        int 21h
        stosb         ; store the character and increment edi
        cmp ecx, 1    ; have we exhausted the space?
        jz out
        dec ecx
        cmp al, 13
        jz terminate  ; pad the end
        jmp while
		
terminate:
        mov al, 10
        stosb
        mov al, '$'
        stosb
out:
       
ret
