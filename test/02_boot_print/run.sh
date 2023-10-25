nasm -f bin boot_main.asm -o boot.bin
qemu-system-i386 boot.bin
