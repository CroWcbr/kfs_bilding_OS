nasm -f bin boot_loop.asm -o boot.bin
qemu-system-i386 boot.bin
