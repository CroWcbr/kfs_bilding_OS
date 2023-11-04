# Boot

- This is the simplest boot sector ever (512 bytes):
```
e9 fd ff 00 00 00 00 00 00 00 00 00 00 00 00 00
[ 30 more lines with sixteen zero-bytes each ]
00 00 00 00 00 00 00 00 00 00 00 00 00 00 55 aa

e9 - JMP instruction
fd ff - represents the relative offset
55 aa - boot sector is valid and can be started
```