; int times2(int n);
_times2:
push bp
mov bp,sp
push di
push si
mov ax,[bp+4]
shl ax,1
pop si
pop di
pop bp
ret
