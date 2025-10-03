.DEFAULT_GOAL 	:=	help

BIN_NAME		=	mykernel.bin
ISO_NAME		=	mykernel.iso

CC 				=	gcc
CC_FLAGS		=	-m32 -Iinclude -fno-builtin -fno-exceptions \
					-fno-stack-protector -fno-rtti -nostdlib \
					-nodefaultlibs -fno-use-cxa-atexit \
					-fno-leading-underscore -Wno-write-strings

ASM				=	as
ASM_FLAGS		=	--32

LDPARAMS		=	-m elf_i386

SRC_DIR			=	./src
SRC_CPP			=	gdt.cpp \
					hardware/port.cpp \
					hardware/interrupts.cpp \
					hardware/syscalls.cpp \
					drivers/driver.cpp \
					drivers/keyboard.cpp \
					drivers/mouse.cpp \
					vga/screen.cpp \
					devicemanager/screenmanager.cpp \
					devicemanager/keyboardmanager.cpp \
					devicemanager/mousemanager.cpp \
					common/stdio.cpp \
					common/print_stack.cpp \
					common/print_shell_promt.cpp \
					common/print_42.cpp \
					common/utils.cpp \
					shell/shell.cpp \
					kernel.cpp

SRC_ASM			=	loader.s \
					hardware/interruptstubs.s

OBJ_DIR			=	obj
OBJECTS			=	$(SRC_CPP:%.cpp=$(OBJ_DIR)/%.o) $(SRC_ASM:%.s=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.cpp
					@mkdir -p $(@D)
					$(CC) $(CC_FLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.s
					mkdir -p $(@D)
					$(ASM) $(ASM_FLAGS) -o $@ $<

bin				:	linker.ld $(OBJECTS)
					ld $(LDPARAMS) -T $< -o $(BIN_NAME) $(OBJECTS)

iso				:	bin
					rm -rf iso
					mkdir iso
					mkdir iso/boot
					mkdir iso/boot/grub
					cp $(BIN_NAME) iso/boot
					echo 'set timeout=0' >> iso/boot/grub/grub.cfg
					echo 'set default=0' >> iso/boot/grub/grub.cfg
					echo '' >> iso/boot/grub/grub.cfg
					echo 'menuentry "CroW Operating System" {' >> iso/boot/grub/grub.cfg
					echo '  multiboot /boot/$(BIN_NAME)' >> iso/boot/grub/grub.cfg
					echo '  boot' >> iso/boot/grub/grub.cfg
					echo '}' >> iso/boot/grub/grub.cfg
					grub-mkrescue --output=$(ISO_NAME) iso
					rm -rf iso

help			:
					@echo "Available targets:"
					@echo "  run     - Run OS inside qemu emulator"
					@echo "  install - Install OS into boot section"
					@echo "  clean   - Remove all files"

install			:	bin
					sudo cp $(BIN_NAME) /boot/$(BIN_NAME)

run				:	iso
					qemu-system-i386 -cdrom $(ISO_NAME)

clean			:
					rm -rf $(OBJ_DIR) $(BIN_NAME) $(ISO_NAME)

.PHONY			:	clean run install help bin iso
