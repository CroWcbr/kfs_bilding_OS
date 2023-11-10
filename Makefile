
CC				=	gcc
CFLAGS			=	-m32 -Iinclude -fno-builtin -fno-exceptions -fno-stack-protector -fno-rtti -nostdlib -nodefaultlibs -fno-use-cxa-atexit \
									-fno-leading-underscore -Wno-write-strings
									
ASPARAMS		=	--32
LDPARAMS		=	-m elf_i386

OBJECTS			=	obj/loader.o \
					obj/gdt.o \
					obj/common/stdio.o \
					obj/drivers/driver.o \
					obj/hardware/port.o \
					obj/hardware/interruptstubs.o \
					obj/hardware/interrupts.o \
					obj/drivers/keyboard.o \
					obj/drivers/mouse.o \
					obj/vga/screen.o \
					obj/kernel.o

obj/%.o			:	src/%.cpp
					mkdir -p $(@D)
					$(CC) $(CFLAGS) -o $@ -c $<

obj/%.o			:	src/%.s
					mkdir -p $(@D)
					as $(ASPARAMS) -o $@ $<

mykernel.bin	:	linker.ld $(OBJECTS)
					ld $(LDPARAMS) -T $< -o $@ $(OBJECTS)

install			:	mykernel.bin
					sudo cp $< /boot/mykernel.bin

mykernel.iso	:	mykernel.bin
					rm -rf iso
					mkdir iso
					mkdir iso/boot
					mkdir iso/boot/grub
					cp $< iso/boot
					echo 'set timeout=0' >> iso/boot/grub/grub.cfg
					echo 'set default=0' >> iso/boot/grub/grub.cfg
					echo '' >> iso/boot/grub/grub.cfg
					echo 'menuentry "CroW Operating System" {' >> iso/boot/grub/grub.cfg
					echo '  multiboot /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
					echo '  boot' >> iso/boot/grub/grub.cfg
					echo '}' >> iso/boot/grub/grub.cfg
					grub-mkrescue --output=$@ iso
					rm -rf iso

run				:	mykernel.iso
					qemu-system-i386 -cdrom mykernel.iso

.PHONY: clean

clean			:
					rm -rf obj mykernel.bin mykernel.iso
