#include <common/types.h>
#include <gdt.h>
#include <hardware/interrupts.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <vga/screenmanager.h>
#include <common/stdio.h>

using namespace crowos;
using namespace crowos::common;
using namespace crowos::drivers;
using namespace crowos::hardware;
using namespace crowos::vga;

class PrintfKeyboardEventHandler : public KeyboardEventHandler
{
public:
	void OnKeyDown(char c)
	{
		Screen& my_screen = Screen::getInstance();
		if (c == '1')
			my_screen.ChangeDisplay(0);
		else if (c == '2')
			my_screen.ChangeDisplay(1);
		else if (c == '3')
			my_screen.ChangeDisplay(2);
		else
		{
			char *foo = " ";
			foo[0] = c;
			my_screen.putchar(c);
		}
	}
};

class MouseToConsole : public MouseEventHandler
{
private:
	int8_t x;
	int8_t y;

public:
	MouseToConsole()
	{
		uint16_t* VideoMemory = (uint16_t*)0xb8000;
		x = 40;
		y = 12;
		VideoMemory[80 * y + x] = ((VideoMemory[80 * y + x] & 0xF000) >> 4)
								| ((VideoMemory[80 * y + x] & 0x0F00) << 4)
								| (VideoMemory[80 * y + x] & 0x00FF);
	}

	void OnMouseMove(int xoffset, int yoffset)
	{
		uint16_t* VideoMemory = (uint16_t*)0xb8000;

		VideoMemory[80 * y + x] = ((VideoMemory[80 * y + x] & 0xF000) >> 4)
								| ((VideoMemory[80 * y + x] & 0x0F00) << 4)
								| (VideoMemory[80 * y + x] & 0x00FF);

		x += xoffset;

		if (x < 0)
			x = 0;
		if (x > 80)
			x = 79;

		y += yoffset;
		if (y < 0)
			y = 0;
		if (y > 25)
			y = 24;

		VideoMemory[80 * y + x] = ((VideoMemory[80 * y + x] & 0xF000) >> 4)
								| ((VideoMemory[80 * y + x] & 0x0F00) << 4)
								| (VideoMemory[80 * y + x] & 0x00FF);
	}
};

typedef void (*constructor)();
constructor start_ctors;
constructor end_ctors;
extern "C" void callConstructors()
{
	for(constructor* i = &start_ctors; i != &end_ctors; i++)
		(*i)();
}

void print_42()
{
	const char *kfs = R"(
##         #######       ##    ## ########  ###### 
##    ##  ##     ##      ##   ##  ##       ##    ##
##    ##         ##      ##  ##   ##       ##      
##    ##   #######       #####    ######    ###### 
######### ##             ##  ##   ##             ##
     ##  ##              ##   ##  ##       ##    ##
     ##  #########       ##    ## ##        ###### 
)";
	printf("%s\n", kfs);
}

extern "C" void kernelMain(void *multiboot_structure, uint32_t magicnumber)
{
	print_42();

	GlobalDescriptorTable gdt;
	InterruptManager interrupts(&gdt);

	DriverManager drvManager;

	MouseToConsole mousehandler;
	MouseDriver mouse(&interrupts, &mousehandler);
	drvManager.AddDriver(&mouse);

	PrintfKeyboardEventHandler kbhandler;
	KeyboardDriver keyboard(&interrupts, &kbhandler);
	drvManager.AddDriver(&keyboard);

	drvManager.ActivateAll();
	interrupts.Activate();

	while(1)
		;
}
