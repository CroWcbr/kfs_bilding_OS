#ifndef __CROW__SCREEN_H
#define __CROW__SCREEN_H

#include <common/types.h>

namespace crowos
{
	namespace vga
	{

		enum Color : crowos::common::uint8_t {
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
				crowos::common::uint8_t		x;
				crowos::common::uint8_t		y;
				crowos::common::int16_t		cursor_position;
				crowos::common::uint16_t	display_buffer[WIDTH * HEIGHT];
				crowos::common::int16_t		buffer_size;
				crowos::common::uint8_t		text_color;
				crowos::common::uint8_t		back_color;
				crowos::common::uint8_t		promt_color;
			};

		protected:
			crowos::common::uint16_t*		VideoMemory;
			screen_info*					active_screen;
			screen_info						screens[MAX_SCREEN];
			static crowos::common::uint8_t	s_text_color;
			static crowos::common::uint8_t	s_back_color;

		private:
			void	setDisplayData(crowos::common::uint16_t *data, crowos::common::uint8_t back_color);
			void	copyFromTo(crowos::common::uint16_t *from, crowos::common::uint16_t *to);

			void	put_slash_n();
			void	put_slash_b();
			void	put_slash_t();
			void	put_symbol(char c, crowos::common::uint8_t text_color, crowos::common::uint8_t back_color);
			void	put_color_char(char c,
									crowos::common::int16_t pos,
									crowos::common::uint8_t text_color, 
									crowos::common::uint8_t back_color);
			void	update_cursor_position();
			void	put_cursor_at();
			void	port_byte_out(crowos::common::uint16_t port, crowos::common::uint8_t data);

		public:
			static Screen&	getInstance();

			void 			ChangeDisplay(crowos::common::uint8_t n);

			void			putchar(char c,
									crowos::common::uint8_t text_color = s_text_color,
									crowos::common::uint8_t back_color = s_back_color);
			
			void			print_shell_promt();

			bool			get_buffer(char *command);
		};

	}
}

#endif
