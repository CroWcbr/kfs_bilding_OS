#include <common/types.h>
#include <gdt.h>
#include <hardware/interrupts.h>
#include <hardware/syscalls.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <devicemanager/keyboardmanager.h>
#include <devicemanager/mousemanager.h>
#include <common/stdio.h>

typedef void (*constructor)();
constructor start_ctors;
constructor end_ctors;
extern "C" void callConstructors()
{
	for(constructor* i = &start_ctors; i != &end_ctors; i++)
		(*i)();
}
namespace crowos
{

extern "C" void kernelMain(void *multiboot_structure, uint32 magicnumber)
{
	GlobalDescriptorTable gdt;
	hardware::InterruptManager interrupts(&gdt);
	hardware::SyscallHandler syscalls(&interrupts, 0x80);

	drivers::DriverManager drvManager;

	devicemanager::MouseToConsole mousehandler;
	drivers::MouseDriver mouse(&interrupts, &mousehandler);
	drvManager.AddDriver(&mouse);

	devicemanager::PrintfKeyboardEventHandler kbhandler;
	drivers::KeyboardDriver keyboard(&interrupts, &kbhandler);
	drvManager.AddDriver(&keyboard);

	drvManager.ActivateAll();
	interrupts.Activate();

// kfs-1 demonstration
	// common::print_42();
	// printf("%s : %d\n", "this is ", 5);

// kfs-2 demonstration
	// print_stack((void*)0);
	// print_stack((void*)0x00000800);
	// print_stack((void*)&gdt);
	// print_stack((void*)0x1);

// kfs-4 demonstration main
	// asm volatile("int $0x2D");	// IRQ 0x 20-2F
	// asm volatile("int $0x00");	// ISR 0x 00-1F
// kfs-4 demonstration bonus syscalls
    // char *str = "123456";
	// int len = 5;
    // asm("int $0x80" : : "a" (4), "b" (str), "c" (len));

	print_shell_promt();
	while(1)
	{
		asm volatile("hlt");
	}
}

} // namespace crowos