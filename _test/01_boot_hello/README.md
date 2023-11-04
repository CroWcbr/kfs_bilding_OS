### Boot "Hellp"

- Teletypewriter(tty) mode for output using BIOS functions
```
mov ah, 0x0e
```
- interrupt for video services (print al register)
```
int 0x10
```
- infinity loop
```
jmp $
```
- show bin file
```
hexdump -C boot.bin

00000000  b4 0e b0 48 cd 10 b0 65  cd 10 b0 6c cd 10 cd 10  |...H...e...l....|
00000010  b0 6f cd 10 eb fe 00 00  00 00 00 00 00 00 00 00  |.o..............|
*
000001f0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 55 aa  |..............U.|

b4 XX - load value XX to ah (tty mode)
b0 XX - load value XX to al
cd XX - interrupts XX (0x10 - print al)
eb fe - infinite loop
```