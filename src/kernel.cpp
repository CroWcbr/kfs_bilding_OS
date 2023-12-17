#include <common/types.h>
#include <gdt.h>
#include <hardware/interrupts.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <devicemanager/keyboardmanager.h>
#include <devicemanager/mousemanager.h>
#include <common/stdio.h>

using namespace crowos;
using namespace crowos::common;
using namespace crowos::drivers;
using namespace crowos::hardware;
using namespace crowos::devicemanager;

typedef void (*constructor)();
constructor start_ctors;
constructor end_ctors;
extern "C" void callConstructors()
{
	for(constructor* i = &start_ctors; i != &end_ctors; i++)
		(*i)();
}

extern "C" void kernelMain(void *multiboot_structure, uint32_t magicnumber)
{
	GlobalDescriptorTable gdt;
	InterruptManager interrupts(&gdt);

	DriverManager drvManager;

// for myself (problem with change screen, multiple cursor - need use class screen for print)
	// MouseToConsole mousehandler;
	// MouseDriver mouse(&interrupts, &mousehandler);
	// drvManager.AddDriver(&mouse);

	PrintfKeyboardEventHandler kbhandler;
	KeyboardDriver keyboard(&interrupts, &kbhandler);
	drvManager.AddDriver(&keyboard);

	drvManager.ActivateAll();
	interrupts.Activate();

// kfs-1 demonstration
	// print_42();
	// printf("%s : %d", "this is ", 5);

// kfs-2 demonstration
	// print_stack((void*)0);
	// print_stack((void*)0x800);
	// print_stack((void*)&gdt);
	// print_stack((void*)0x1);

// kfs-4 test
	// asm volatile("int $0x00");
	// int x = 0;
	// int y = 10;
	// int xy = y/x;
	// asm volatile("int $0x01");
	// asm volatile("int $0x02");
	// asm volatile("int $0x03");
	// asm volatile("int $0x04");
	// asm volatile("int $0x05");
	// asm volatile("int $0x06");
	// asm volatile("int $0x07");
	// asm volatile("int $0x08");
	// asm volatile("int $0x09");
	// asm volatile("int $0x0A");
	// asm volatile("int $0x0B");
	// asm volatile("int $0x0C");
	// asm volatile("int $0x0D");
	// asm volatile("int $0x0E");
	// asm volatile("int $0x0F");
	// asm volatile("int $0x10");
	// asm volatile("int $0x11");
	// asm volatile("int $0x12");
	// asm volatile("int $0x13");

	print_shell_promt();
	while(1)
		;
}
