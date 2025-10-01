#ifndef __CROW__SCREEN_H
#define __CROW__SCREEN_H

#include <common/types.h>

namespace crowos
{
	namespace vga
	{

		enum Color : uint8
		{
			BLACK,
			BLUE,
			GREEN,
			CYAN,
			RED,
			MAGENTA,
			BROWN,
			LIGHT_GRAY,
			DARK_GRAY,
			LIGHT_BLUE,
			LIGHT_GREEN,
			LIGHT_CYAN,
			LIGHT_RED,
			LIGHT_MAGENTA,
			YELLOW,
			WHITE
		};

		#define WIDTH			80
		#define HEIGHT			25
		#define MAX_BUFFER		200
		#define MAX_SCREEN		3
		#define PROMT_TEXT		"CroW@kfs> "

		class Screen
		{
		private:
			struct screen_info
			{
				uint8		x;
				uint8		y;
				int16		cursor_position;
				uint16		display_buffer[WIDTH * HEIGHT];
				int16		buffer_size;
				uint8		text_color;
				uint8		back_color;
				uint8		promt_color;
				uint8		mouse_color;
				uint8		x_mouse;
				uint8		y_mouse;
				int16		mouse_position;
				uint16		mouse_bg_saved;
			};

		protected:
			uint16*			VideoMemory;
			screen_info*	active_screen;
			screen_info		screens[MAX_SCREEN];
			static uint8	s_text_color;
			static uint8	s_back_color;
			static uint8	s_mouse_color;

		private:
			void	setDisplayData(uint16 *data, uint8 back_color);
			void	copyFromTo(uint16 *from, uint16 *to);

			void	put_slash_n();
			void	put_slash_b();
			void	put_slash_t();
			void	put_symbol(char c, uint8 text_color, uint8 back_color);
			void	put_color_char(char c,
									int16 pos,
									uint8 text_color, 
									uint8 back_color);
			void	update_cursor_position();
			void	put_cursor_at();
			void	port_byte_out(uint16 port, uint8 data);

		public:
			static Screen&	getInstance();

			void 			ChangeDisplay(uint8 n);

			void			putchar(char c,
									uint8 text_color = s_text_color,
									uint8 back_color = s_back_color);
			
			void			print_shell_promt();

			bool			get_buffer(char *command);

			void			clear();

			void			mouse_position(int8 x, int8 y);
			void			draw_mouse(bool visible);
			void 			init_cursor();
		};

	} // namespace vga

} // namespace crowos

#endif
