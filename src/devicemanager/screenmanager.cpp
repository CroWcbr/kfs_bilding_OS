#include <devicemanager/screenmanager.h>
#include <common/stdio.h>
#include <hardware/port.h>
#include <shell/shell.h>

using namespace crowos::vga;
using namespace crowos::devicemanager;
using namespace crowos::common;
using namespace crowos::hardware;
using namespace crowos::shell;

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
	char command[10 + 1]; //max 10 symbol
	my_screen->get_buffer(command); //get_line
	putchar('\n');
	Shell::exec_cmd(command, my_screen);

}
