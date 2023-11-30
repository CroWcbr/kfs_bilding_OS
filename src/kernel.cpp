#include <common/types.h>
#include <gdt.h>
#include <hardware/interrupts.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <devicemanager/screenmanager.h>
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

static unsigned int my_rand()
{
	static unsigned int my_rand_seed = 42;
	my_rand_seed = my_rand_seed * 1103515245  + 12345;
	return my_rand_seed % 16;
}

void print_42()
{
	Screen& my_screen = Screen::getInstance();
	const char *kfs = R"(
##         #######     ##    ## ########  ######  
##    ##  ##     ##    ##   ##  ##       ##    ## 
##    ##         ##    ##  ##   ##       ##       
##    ##   #######     #####    ######    ######  
######### ##           ##  ##   ##             ## 
      ##  ##           ##   ##  ##       ##    ## 
      ##  #########    ##    ## ##        ######  

)";
	for (int i = 0; kfs[i]; ++i)
	{
		if (kfs[i] == ' ' || kfs[i] == '\n')
			my_screen.putchar(kfs[i]);
		else
			my_screen.putchar(' ', 0, my_rand());
	}
}

extern "C" void kernelMain(void *multiboot_structure, uint32_t magicnumber)
{
	// print_42();

	GlobalDescriptorTable gdt;
printf("GDT: %p\n", &gdt);
	InterruptManager interrupts(&gdt);

	DriverManager drvManager;

// 	MouseToConsole mousehandler;
// 	MouseDriver mouse(&interrupts, &mousehandler);
// 	drvManager.AddDriver(&mouse);

	PrintfKeyboardEventHandler kbhandler;
	KeyboardDriver keyboard(&interrupts, &kbhandler);
	drvManager.AddDriver(&keyboard);

	drvManager.ActivateAll();
	interrupts.Activate();

// uint8_t* test = (uint8_t*)(&gdt);
// int numBytes = 32;

// printf("%p\n", test);
// for (int i = 0; i < numBytes; ++i) {
// 	printf("0x%p ", test[i]);
// 	if (i != 0 && (i + 1) % 8 == 0)
// 		printf("\n");
// }
// printf("\n");

// test = (uint8_t*)(0x800);

// printf("%p\n", test);
// for (int i = 0; i < numBytes; ++i) {
// 	printf("0x%p ", test[i]);
// 	if (i != 0 && (i + 1) % 8 == 0)
// 		printf("\n");
// }
// printf("\n");

	while(1)
		;
}
