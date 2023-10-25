./clear.sh
make kernel.o
make loader.o
make mykernel.bin
qemu-system-i386 -kernel mykernel.bin