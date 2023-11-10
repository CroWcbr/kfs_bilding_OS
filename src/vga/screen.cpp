#include <vga/screen.h>

using namespace crowos::vga;
using namespace crowos::common;

Screen& Screen::getInstance()
{
	static Screen instance;
	static bool initialized = false;
	if (!initialized)
	{
		instance.VideoMemory = (uint16_t*)0xb8000;
		instance.clearDisplayBuffer(instance.VideoMemory);
		for (int i = 0; i < MAX_SCREEN; ++i)
		{
			instance.screens[i].x = 0;
			instance.screens[i].y = 0;
			instance.screens[i].cursor_position = 0;
			instance.copyFromTo(instance.VideoMemory, instance.screens[i].display_buffer);
			instance.screens[i].buffer_size = 0;
			// instance.clearDataBuffer(instance.screens[i].data_buffer);
		}
		instance.active_screen = &(instance.screens[0]);
		initialized = true;
	}
	return instance;
}

void Screen::clearDisplayBuffer(uint16_t *data)
{
	for (int i = 0; i < WIDTH * HEIGHT; ++i)
		data[i] = (data[i] & 0xFF00) | ' ';
}

void Screen::copyFromTo(uint16_t *from, uint16_t *to)
{
	for (int i = 0; i < WIDTH * HEIGHT; ++i)
		to[i] = from[i];
}

// void Screen::clearDataBuffer(uint8_t *data)
// {
// 	for (int i = 0; i < WIDTH * HEIGHT; ++i)
// 		data[i] = 0;
// }

void	Screen::ChangeDisplay(uint8_t n)
{
	if (n > MAX_SCREEN || active_screen == &screens[n])
		return ;

	copyFromTo(VideoMemory, active_screen->display_buffer);
	active_screen = &screens[n];
	copyFromTo(active_screen->display_buffer, VideoMemory);

	put_cursor_at();
}

void	Screen::putchar(char c)
{
	switch(c)
	{
		case '\n':
			active_screen->y++;
			active_screen->x = 0;
			active_screen->cursor_position = 80 * active_screen->y + active_screen->x;
			active_screen->buffer_size = 0;
			break;
		case '\b':
			if(active_screen->cursor_position && active_screen->buffer_size)
			{
				active_screen->cursor_position--;
				active_screen->buffer_size--;
				VideoMemory[active_screen->cursor_position] = (VideoMemory[active_screen->cursor_position] & 0xFF00) | ' ';
				if (active_screen->y && active_screen->x == 0)
				{
					active_screen->y--;
					active_screen->x = 79;
				}
				else if(active_screen->x)
					active_screen->x--;
			}
			break;
		case '\t':
			for(int i = 0, pos = 4 - active_screen->x % 4; i < pos ; ++i)
				putchar(' ');
			break;
		default:
			VideoMemory[active_screen->cursor_position] = (VideoMemory[active_screen->cursor_position] & 0xFF00) | c;
			active_screen->x++;
			active_screen->cursor_position++;
			active_screen->buffer_size++;
			break;
	}

	if (active_screen->x >= 80)
	{
		active_screen->y++;
		active_screen->x = 0;
	}

	if (active_screen->y >= 25)
	{
		int row = 10;
		int row_delta = WIDTH * (HEIGHT - row);
		for (int i = 0; i < WIDTH * row; ++i)
			VideoMemory[i] = VideoMemory[i + row_delta];
		for (int i = WIDTH * row; i < WIDTH * HEIGHT; ++i)
			VideoMemory[i] = (VideoMemory[i] & 0xFF00) | ' ';
		active_screen->y = row;
		active_screen->cursor_position = 80 * active_screen->y + active_screen->x;
		if (active_screen->cursor_position < active_screen->buffer_size)
			active_screen->buffer_size = active_screen->cursor_position;
	}
	put_cursor_at();
}

void Screen::port_byte_out(uint16_t port, uint8_t data)
{
	asm volatile ("outb %0, %1" :: "a"(data), "Nd"(port));
}

void Screen::put_cursor_at()
{
	port_byte_out(0x3d4, 0xe);
	port_byte_out(0x3d5, active_screen->cursor_position >> 8);
	port_byte_out(0x3d4, 0xf);
	port_byte_out(0x3d5, active_screen->cursor_position);
}
