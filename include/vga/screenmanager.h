#ifndef __CROW__SCREENMANAGER_H
#define __CROW__SCREENMANAGER_H

#include <vga/screen.h>

namespace crowos
{
	namespace vga
	{
		const char g_HexChars[] = "0123456789abcdef";

		class ScreenManager
		{
		private:
			unsigned long long	custom_divide_64bit(unsigned long long numerator, int denominator, int *remainder);

		protected:
			Screen	*my_screen;

		public:
			static ScreenManager&	getInstance();

			void			putchar(char c);
			void			putstr(const char* str);
			void			printf_unsigned_long(unsigned long number, int radix);
			void			printf_signed_long(long number, int radix);
			void			printf_unsigned_long_long(unsigned long long number, int radix);
			void			printf_signed_long_long(long long number, int radix);
		};

	}
}

#endif