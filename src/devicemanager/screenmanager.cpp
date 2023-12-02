#include <devicemanager/screenmanager.h>
#include <common/stdio.h>
#include <hardware/port.h>

using namespace crowos::vga;
using namespace crowos::devicemanager;
using namespace crowos::common;
using namespace crowos::hardware;

ScreenManager& ScreenManager::getInstance()
{
	static ScreenManager instance;
	static bool initialized = false;
	if (!initialized)
	{
		instance.my_screen = &(Screen::getInstance());
		initialized = true;
	}
	return instance;
}

void	ScreenManager::ChangeDisplay(uint8_t n)
{
	my_screen->ChangeDisplay(n);
}

void	ScreenManager::put_color_char(char c, uint8_t text_color, uint8_t back_color)
{
	my_screen->putchar(c, text_color, back_color);
}

void	ScreenManager::put_color_char(char c, uint8_t text_color)
{
	my_screen->putchar(c, text_color);
}

void	ScreenManager::putchar(char c)
{
	my_screen->putchar(c);
}

void	ScreenManager::print_shell_promt()
{
	my_screen->print_shell_promt();
}

// extern "C" char readPort(unsigned short port);
// extern "C" void writePort(unsigned short port, unsigned char data);

void	ScreenManager::check_command()
{
	char command[10];
	if(my_screen->get_buffer(command))
	{
		putchar('\n');
		printf("%s\n", command);
		if (command[0] == 's')
		{
			print_stack();
			putchar('\n');
		}
		else if (command[0] == 'r')
		{
			uint8_t good = 0x02;

			Port16bit dataport(0x64);
			// Poll bit 1 of the Status Register ("Input buffer empty/full") until it becomes clear.
			while (good & 0x02)
				good = dataport.Read();

			// Set the reset line bit to 0
			dataport.Write(0xFE);
			__asm__ ("hlt");
		}
		else if (command[0] == 'o')
		{
			Port16bit dataport(0x604);
			dataport.Write(0x2000); // for QEMU
			// dataport.Write(0x3400); // for VM
		}
		else if (command[0] == 'h')
		{
			__asm__ ("hlt");
			__asm__ ("int $0x3");
		}
	}
	else
		putchar('\n');
	// my_screen->print_shell_promt();
}