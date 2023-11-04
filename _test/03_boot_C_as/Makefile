
CC				=	gcc
CFLAGS			=	-m32 -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti -nostdlib -nodefaultlibs
ASPARAMS		=	--32
LDPARAMS		=	-m elf_i386

OBJECTS			=	loader.o kernel.o

%.o				:	%.c
					$(CC) $(CFLAGS) -o $@ -c $<

%.o				:	%.s
					as $(ASPARAMS) -o $@ $<

mykernel.bin	:	linker.ld $(OBJECTS)
					ld $(LDPARAMS) -T $< -o $@ $(OBJECTS)

install			:	mykernel.bin
					sudo cp $< /boot/mykernel.bin
