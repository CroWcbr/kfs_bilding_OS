#include <common/stdio.h>
#include <common/stdarg.h>
#include <vga/screen.h>

using namespace crowos::vga;

namespace crowos
{
	namespace common
	{

		static void	putc(char c)
		{
			Screen& my_screen = Screen::getInstance();
			my_screen.putchar(c);
		}

		static void	puts(const char* str)
		{
			for(int i = 0; str[i] != '\0'; ++i)
				putc(str[i]);
		}

		static void	printf_unsigned_long(unsigned long number, int radix)
		{
			char buffer[32];
			int pos = 0;

			do 
			{
				unsigned long rem = number % radix;
				number /= radix;
				buffer[pos++] = g_HexChars[rem];
			} while (number > 0);

			while (--pos >= 0)
				putc(buffer[pos]);
		}

		static void printf_signed_long(long number, int radix)
		{
			if (number < 0)
			{
				putc('-');
				printf_unsigned_long(-number, radix);
			}
			else
				printf_unsigned_long(number, radix);
		}

		void printf(const char* fmt, ...)
		{
			va_list args;
			va_start(args, fmt);

			int state = PRINTF_STATE_NORMAL;
			int length = PRINTF_LENGTH_DEFAULT;
			int radix = 10;
			bool sign = false;
			bool number = false;

			while(*fmt)
			{
				switch (state)
				{
					case PRINTF_STATE_NORMAL:
						switch (*fmt)
						{
							case '%':
								state = PRINTF_STATE_LENGTH;
								break;
							default:
								putc(*fmt);
								break;
						}
						break;

					case PRINTF_STATE_LENGTH:
						switch (*fmt)
						{
							case 'h':
								length = PRINTF_LENGTH_SHORT;
								state = PRINTF_STATE_LENGTH_SHORT;
								break;
							case 'l':
								length = PRINTF_LENGTH_LONG;
								state = PRINTF_STATE_LENGTH_LONG;
								break;
							default:
								goto PRINTF_STATE_SPEC_;
						}
						break;

					case PRINTF_STATE_LENGTH_SHORT:
						if (*fmt == 'h')
						{
							length = PRINTF_LENGTH_SHORT_SHORT;
							state = PRINTF_STATE_SPEC;
						}
						else
							goto PRINTF_STATE_SPEC_;
						break;

					case PRINTF_STATE_LENGTH_LONG:
						if (*fmt == 'l')
						{
							length = PRINTF_LENGTH_LONG_LONG;
							state = PRINTF_STATE_SPEC;
						}
						else
							goto PRINTF_STATE_SPEC_;
						break;

					case PRINTF_STATE_SPEC:
					PRINTF_STATE_SPEC_:
						switch (*fmt)
						{
						case 'c':
							putc((char)va_arg(args, int));
							break;
						case 's':
							puts(va_arg(args, const char*));
							break;
						case '%':
							putc('%');
							break;
						case 'd':
						case 'i':
							radix = 10;
							sign = true;
							number = true;
							break;
						case 'u':
							radix = 10;
							sign = false;
							number = true;
							break;
						case 'X':
						case 'x':
						case 'p':
							radix = 16;
							sign = false;
							number = true;
							break;
						case 'o':
							radix = 8;
							sign = false;
							number = true;
							break;
						default:
							break;
						}

						if (number)
						{
							if (sign)
							{
								switch (length)
								{
								case PRINTF_LENGTH_SHORT_SHORT:
								case PRINTF_LENGTH_SHORT:
								case PRINTF_LENGTH_DEFAULT:
									printf_signed_long(va_arg(args, int), radix);
									break;

								case PRINTF_LENGTH_LONG:
									printf_signed_long(va_arg(args, long), radix);
									break;

								case PRINTF_LENGTH_LONG_LONG:
									puts("long long - don't work");
									// printf_signed(va_arg(args, long long), radix);
									break;
								}
							}
							else
							{
								switch (length)
								{
								case PRINTF_LENGTH_SHORT_SHORT:
								case PRINTF_LENGTH_SHORT:
								case PRINTF_LENGTH_DEFAULT:
									printf_unsigned_long(va_arg(args, unsigned int), radix);
									break;

								case PRINTF_LENGTH_LONG:
									printf_unsigned_long(va_arg(args, unsigned long), radix);
									break;

								case PRINTF_LENGTH_LONG_LONG:
									puts("unsigned long long - don't work");
									// printf_unsigned(va_arg(args, unsigned long long), radix);
									break;
								}
							}
						}

					state = PRINTF_STATE_NORMAL;
					length = PRINTF_LENGTH_DEFAULT;
					radix = 10;
					sign = false;
					number = false;
					break;
				}
				fmt++;
			}
		}

	}
}
