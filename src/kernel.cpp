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
using namespace crowos::vga;
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
// kfs-1 demonstration
	// print_42();
	// printf("%s : %d", "this is ", 5);

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

// kfs-2 demonstration
	// print_stack();
	// print_stack((void*)0x800);
	// print_stack((void*)&gdt);

	print_shell_promt();
	while(1)
		;
}
