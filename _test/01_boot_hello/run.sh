nasm -f bin boot_hello.asm -o boot.bin
qemu-system-i386 boot.bin
