#include <devicemanager/screenmanager.h>
#include <common/stdio.h>
#include <hardware/port.h>
#include <shell/shell.h>

namespace crowos::devicemanager
{

ScreenManager& ScreenManager::getInstance()
{
	static ScreenManager instance;
	static bool initialized = false;
	if (!initialized)
	{
		instance.my_screen = &(vga::Screen::getInstance());
		initialized = true;
	}
	return instance;
}

void	ScreenManager::ChangeDisplay(uint8 n)
{
	my_screen->ChangeDisplay(n);
}

void	ScreenManager::put_color_char(char c, uint8 text_color, uint8 back_color)
{
	my_screen->putchar(c, text_color, back_color);
}

void	ScreenManager::put_color_char(char c, uint8 text_color)
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
	char command[10 + 1]; //max 10 symbol
	my_screen->get_buffer(command); //get_line
	putchar('\n');
	shell::Shell::exec_cmd(command);
}

void	ScreenManager::mouse_position(int8 x, int8 y)
{
	my_screen->mouse_position(x,y);
}

} // crowos::devicemanager