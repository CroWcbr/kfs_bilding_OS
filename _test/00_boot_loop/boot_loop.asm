; Fill with 510 zeros minus the size of the previous code
times 510-($-$$) db 0
; Magic number (last 2 bytes)
dw 0xaa55

; Infinite loop (e9 fd ff)
loop:
    jmp loop
