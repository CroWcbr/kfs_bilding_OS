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
			vga::Screen		*my_screen;

		public:
			static ScreenManager&	getInstance();

			void			ChangeDisplay(uint8 n);

			void			print_shell_promt();
			void			putchar(char c);
			void			put_color_char(char c, uint8 text_color, uint8 back_color);
			void			put_color_char(char c, uint8 text_color);

			void			check_command();

			void			mouse_position(int8 x, int8 y);
		};

	} // namespace devicemanager

} // namespace crowos

#endif
