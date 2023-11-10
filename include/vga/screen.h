#ifndef __CROW__SCREEN_H
#define __CROW__SCREEN_H

#include <common/types.h>

namespace crowos
{
	namespace vga
	{
		#define WIDTH		80
		#define HEIGHT		25
		#define MAX_BUFFER	200
		#define MAX_SCREEN	3

		class Screen
		{
		private:
			struct screen_info
			{
				crowos::common::uint8_t		x;
				crowos::common::uint8_t		y;
				crowos::common::int16_t		cursor_position;
				crowos::common::uint16_t	display_buffer[WIDTH * HEIGHT];
				crowos::common::uint8_t		data_buffer[MAX_BUFFER];
			};

			void	clearDisplayBuffer(crowos::common::uint16_t *data);
			void	clearDataBuffer(crowos::common::uint8_t *buffer);
			void	put_cursor_at();
			void	port_byte_out(crowos::common::uint16_t port, crowos::common::uint8_t data);

		protected:
			crowos::common::uint16_t*	VideoMemory;
			screen_info*				active_screen;
			screen_info					screens[MAX_SCREEN];

		public:
			static Screen&	getInstance();

			void			putchar(char c);
		};
	}
}

#endif
