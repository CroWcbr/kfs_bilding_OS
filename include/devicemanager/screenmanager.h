#ifndef __CROW__SCREENMANAGER_H
#define __CROW__SCREENMANAGER_H

#include <vga/screen.h>
#include <common/types.h>

namespace crowos
{
	namespace devicemanager
	{
		class ScreenManager
		{
		protected:
			crowos::vga::Screen		*my_screen;

		public:
			static ScreenManager&	getInstance();

			void			ChangeDisplay(crowos::common::uint8_t n);

			void			print_shell_promt();
			void			putchar(char c);
			void			put_color_char(char c, crowos::common::uint8_t text_color, crowos::common::uint8_t back_color);
			void			put_color_char(char c, crowos::common::uint8_t text_color);

			void			check_command();
		};

	}
}

#endif
