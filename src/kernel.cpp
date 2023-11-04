#include <common/types.h>
#include <gdt.h>
#include <hardware/interrupts.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <vga/screen.h>

using namespace crowos;
using namespace crowos::common;
using namespace crowos::drivers;
using namespace crowos::hardware;
using namespace crowos::vga;

void port_byte_out(uint16_t port, uint8_t data)
{
	asm volatile ("outb %0, %1" :: "a"(data), "Nd"(port));
}

// void port_byte_out(uint16 port, uint8 value)
// {
//     asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
// }

#define low_8(address) (uint8_t)((address) & 0xFF)
#define high_8(address) (uint8_t)(((address) >> 8) & 0xFF)
void put_cursor_at(int idx)
{
	port_byte_out(0x3d4, 0xe);
	port_byte_out(0x3d5, high_8(idx));
	port_byte_out(0x3d4, 0xf);
	port_byte_out(0x3d5, low_8(idx));
}

void printk2(const char* str)
{
	static uint16_t* VideoMemory = (uint16_t*)0xb8000;

	static uint8_t x = 0;
	static uint8_t y = 0;

	for(int i = 0; str[i] != '\0'; ++i)
	{
		switch(str[i])
		{
			case '\n':
				y++;
				x = 0;
				// put_cursor_at(80 * y + x);
				break;
			default:
				VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | str[i];
				x++;
				// put_cursor_at(80 * y + x);
				break;
		}
		if (x >= 80)
		{
			y++;
			x = 0;
		}
		if (y>= 25)
		{
			for (int i = 0; i < 80 * 25; ++i)
				VideoMemory[i] = (VideoMemory[i] & 0xFF00) | ' ';
			x = 0;
			y = 0;
		}
	}
}

void printk(const char* str)
{
	// static Screen my_screen;
	Screen& my_screen = Screen::getInstance();
	for(int i = 0; str[i] != '\0'; ++i)
		my_screen.putchar(str[i]);
	// printk2(str);
}

void printkHex(uint8_t key)
{
	char foo[] = "00";
	char hex[] = "0123456789ABCDEF";
	foo[0] = hex[(key >> 4) & 0xF];
	foo[1] = hex[key & 0xF];
	printk(foo);
}

class PrintfKeyboardEventHandler : public KeyboardEventHandler
{
public:
	void OnKeyDown(char c)
	{
		char *foo = " ";
		foo[0] = c;
		printk(foo);
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

extern "C" void kernelMain(void *multiboot_structure, uint32_t magicnumber)
{
	printk("Hello World!\n");

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
