#include <vga/screen.h>

using namespace crowos::vga;
using namespace crowos::common;

crowos::common::uint8_t Screen::s_text_color;
crowos::common::uint8_t Screen::s_back_color;

Screen& Screen::getInstance()
{
	static Screen instance;
	static bool initialized = false;
	if (!initialized)
	{
		instance.VideoMemory = (uint16_t*)0xb8000;

		instance.screens[0].text_color = Color::WHITE;
		instance.screens[0].back_color = Color::BLACK;
		instance.screens[0].promt_color = Color::GREEN;
		instance.screens[1].text_color = Color::DARK_GRAY;
		instance.screens[1].back_color = Color::BLUE;
		instance.screens[1].promt_color = Color::WHITE;
		instance.screens[2].text_color = Color::LIGHT_CYAN;
		instance.screens[2].back_color = Color::DARK_GRAY;
		instance.screens[2].promt_color = Color::GREEN;

		for (int i = 0; i < MAX_SCREEN; ++i)
		{
			instance.screens[i].x = 0;
			instance.screens[i].y = 0;
			instance.screens[i].cursor_position = 0;
			instance.setDisplayData(instance.screens[i].display_buffer, instance.screens[i].back_color);
			instance.screens[i].buffer_size = 0;
		}
		instance.active_screen = &(instance.screens[0]);
		instance.copyFromTo(instance.active_screen->display_buffer, instance.VideoMemory);
		instance.s_text_color = instance.screens[0].text_color;
		instance.s_back_color = instance.screens[0].back_color;
		initialized = true;
	}
	return instance;
}

void	Screen::setDisplayData(uint16_t *data, uint8_t back_color)
{
	uint8_t text_color = 0xF;
	for (int i = 0; i < WIDTH * HEIGHT; ++i)
		data[i] = ((text_color | (back_color << 4)) << 8) | ' ';
}

void Screen::copyFromTo(uint16_t *from, uint16_t *to)
{
	for (int i = 0; i < WIDTH * HEIGHT; ++i)
		to[i] = from[i];
}

void	Screen::ChangeDisplay(uint8_t n)
{
	if (n > MAX_SCREEN || active_screen == &screens[n])
		return ;

	copyFromTo(VideoMemory, active_screen->display_buffer);
	active_screen = &screens[n];
	copyFromTo(active_screen->display_buffer, VideoMemory);
	s_text_color = active_screen->text_color;
	s_back_color = active_screen->back_color;
	if (active_screen->x == 0 && active_screen->buffer_size == 0)
		print_shell_promt();
	else
		put_cursor_at();
}

void	Screen::putchar(char c, uint8_t text_color, uint8_t back_color)
{
	switch(c)
	{
		case '\n':
			put_slash_n();
			break;
		case '\b':
			put_slash_b();
			break;
		case '\t':
			put_slash_t();
			break;
		default:
			put_symbol(c, text_color, back_color);
			break;
	}
	update_cursor_position();
}

void Screen::put_color_char(char c, int16_t pos, uint8_t text_color, uint8_t back_color)
{
	// Bit:     | 15 14 13 12 11 10 9 8 | 7 6 5 4 | 3 2 1 0 |
	// Content: | ASCII                 | FG      | BG      |
	VideoMemory[pos] = ((text_color | (back_color << 4)) << 8) | c;
}

void Screen::put_symbol(char c, uint8_t text_color, uint8_t back_color)
{
	put_color_char(c, active_screen->cursor_position, text_color, back_color);
	active_screen->x++;
	active_screen->cursor_position++;
	active_screen->buffer_size++;
}

void Screen::put_slash_n()
{
	active_screen->y++;
	active_screen->x = 0;
	active_screen->cursor_position = 80 * active_screen->y + active_screen->x;
	active_screen->buffer_size = 0;
}

void Screen::put_slash_b()
{
	if(active_screen->cursor_position && active_screen->buffer_size)
	{
		active_screen->cursor_position--;
		active_screen->buffer_size--;
		put_color_char(' ', active_screen->cursor_position, s_text_color, s_back_color);
		if (active_screen->y && active_screen->x == 0)
		{
			active_screen->y--;
			active_screen->x = 79;
		}
		else if(active_screen->x)
			active_screen->x--;
	}
}

void Screen::put_slash_t()
{
	for(int i = 0, pos = 4 - active_screen->x % 4; i < pos ; ++i)
	{
		active_screen->x++;
		active_screen->cursor_position++;
		active_screen->buffer_size++;
	}
}

void	Screen::update_cursor_position()
{
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
			put_color_char(' ', i, s_text_color, s_back_color);
		active_screen->y = row;
		active_screen->cursor_position = 80 * active_screen->y + active_screen->x;
		if (active_screen->cursor_position < active_screen->buffer_size)
			active_screen->buffer_size = active_screen->cursor_position;
	}
	put_cursor_at();
}

void Screen::port_byte_out(uint16_t port, uint8_t data)
{
	// work like Class port
	asm volatile ("outb %0, %1" :: "a"(data), "Nd"(port));
}

void Screen::put_cursor_at()
{
	port_byte_out(0x3d4, 0xe);									// 0xe tells the framebuffer to expect the highest 8 bits of the position
	port_byte_out(0x3d5, active_screen->cursor_position >> 8);	// sending the highest 8 bits of cursor position
	port_byte_out(0x3d4, 0xf);									// 0xf tells the framebuffer to expect the lowest 8 bits of the position
	port_byte_out(0x3d5, active_screen->cursor_position);		// sending the lowest 8 bits of cursor position
}

void Screen::print_shell_promt()
{
	for (int i = 0; PROMT_TEXT[i]; ++i)
	{
		put_color_char(PROMT_TEXT[i], active_screen->cursor_position, active_screen->promt_color, active_screen->back_color);
		active_screen->x++;
		active_screen->cursor_position++;
	}
	put_cursor_at();
}

bool	Screen::get_buffer(char *command)
{
	if (active_screen->buffer_size > 10)
		return false;

	int pos = active_screen->cursor_position - active_screen->buffer_size;
	int i = 0;
	for(; i < active_screen->buffer_size; ++i)
		command[i] = (uint8_t)VideoMemory[pos + i];
	command[i] = 0;
	return true;
}

void	Screen::clear()
{
	setDisplayData(VideoMemory, active_screen->back_color);
	active_screen->x = 0;
	active_screen->y = 0;
	active_screen->cursor_position = 0;
	active_screen->buffer_size = 0;
	put_cursor_at();
}
