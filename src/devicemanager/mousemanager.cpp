#include <devicemanager/mousemanager.h>

namespace crowos::devicemanager
{

MouseToConsole::MouseToConsole()
{
	my_screen = &(ScreenManager::getInstance());
}

void MouseToConsole::OnMouseMove(int8 xoffset, int8 yoffset)
{
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

	my_screen->mouse_position(x, y);
}

} // namespace crowos::devicemanager