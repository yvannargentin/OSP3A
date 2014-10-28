;void write_sector(int sector, uchar *buf);
.global write_sector

write_sector:
; init the stack
push bp
mov bp,sp
push si


