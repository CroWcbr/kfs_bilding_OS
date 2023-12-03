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

void	ScreenManager::check_command()
{
/* I need o make additional class Shell and realized all this function there...
But it is boring, may be I do it in future...
Good style :
	static class Shell
	strcmp, strncmp
*/
	char command[10 + 1]; //max 10 symbol
	if(my_screen->get_buffer(command))
	{
		putchar('\n');
		if (command[0] == 's' && \
			command[1] == 't' && \
			command[2] == 'a' && \
			command[3] == 'c' && \
			command[4] == 'k' && \
			command[5] == 0)
		{
			int x;
			__asm__ ("mov %%esp, %0" : "=r"(x) ::); // stack pointer
			print_stack((uint8_t*)x);
		}
		else if (command[0] == 'r' && \
				command[1] == 'e' && \
				command[2] == 'b' && \
				command[3] == 'o' && \
				command[4] == 'o' && \
				command[5] == 't' && \
				command[6] == 0)
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
		else if (command[0] == 's' && \
				command[1] == 'h' && \
				command[2] == 'u' && \
				command[3] == 't' && \
				command[4] == 'd' && \
				command[5] == 'o' && \
				command[6] == 'w' && \
				command[7] == 'n' && \
				command[8] == 0)
		{
			Port16bit dataport(0x604);
			dataport.Write(0x2000); // for QEMU
			// dataport.Write(0x3400); // for VM
		}
		else if (command[0] == 'h' && \
				command[1] == 'a' && \
				command[2] == 'l' && \
				command[3] == 't' && \
				command[4] == 0)
		{
			__asm__ ("hlt");
			__asm__ ("int $0x3");
		}
	}
	else
		putchar('\n');
	// my_screen->print_shell_promt();
}
