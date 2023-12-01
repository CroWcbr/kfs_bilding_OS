#ifndef __CROW__SCREENMANAGER_H
#define __CROW__SCREENMANAGER_H

#include <vga/screen.h>
#include <common/types.h>

namespace crowos
{
	namespace devicemanager
	{
		#define HEX_CHARS "0123456789abcdef"

		class ScreenManager
		{
		private:
			unsigned long long	custom_divide_64bit(unsigned long long numerator, int denominator, int *remainder);

		protected:
			crowos::vga::Screen	*my_screen;

		public:
			static ScreenManager&	getInstance();

			void			put_color_char(char c, crowos::common::uint8_t text_color, crowos::common::uint8_t back_color);
			void			put_color_char(char c, crowos::common::uint8_t text_color);
			void			putchar(char c);
			void			putstr(const char* str);
			void			printf_unsigned_long(unsigned long number, int radix);
			void			printf_signed_long(long number, int radix);
			void			printf_unsigned_long_long(unsigned long long number, int radix);
			void			printf_signed_long_long(long long number, int radix);

			void			ChangeDisplay(crowos::common::uint8_t n);

			void			print_shell_promt();
		};

	}
}

#endif
