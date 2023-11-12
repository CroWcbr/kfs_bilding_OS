#include <devicemanager/mousemanager.h>

using namespace crowos::devicemanager;
using namespace crowos::common;

MouseToConsole::MouseToConsole()
{
	uint16_t* VideoMemory = (uint16_t*)0xb8000;
	x = 40;
	y = 12;
	VideoMemory[80 * y + x] = ((VideoMemory[80 * y + x] & 0xF000) >> 4)
							| ((VideoMemory[80 * y + x] & 0x0F00) << 4)
							| (VideoMemory[80 * y + x] & 0x00FF);
}

void MouseToConsole::OnMouseMove(int xoffset, int yoffset)
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
