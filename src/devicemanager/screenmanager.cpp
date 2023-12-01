#include <devicemanager/screenmanager.h>

using namespace crowos::vga;
using namespace crowos::devicemanager;
using namespace crowos::common;

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
