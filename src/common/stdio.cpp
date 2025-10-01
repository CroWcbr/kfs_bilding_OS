#include <common/stdio.h>
#include <common/stdarg.h>
#include <devicemanager/screenmanager.h>

namespace crowos
{
	namespace common
	{

	namespace
	{
		#define PRINTF_STATE_NORMAL			0
		#define PRINTF_STATE_LENGTH			1
		#define PRINTF_STATE_LENGTH_SHORT	2
		#define PRINTF_STATE_LENGTH_LONG	3
		#define PRINTF_STATE_SPEC			4

		#define PRINTF_LENGTH_DEFAULT		0
		#define PRINTF_LENGTH_SHORT_SHORT	1
		#define PRINTF_LENGTH_SHORT			2
		#define PRINTF_LENGTH_LONG			3
		#define PRINTF_LENGTH_LONG_LONG		4

		#define HEX_CHARS "0123456789abcdef"

		static void	putchar(char c)
		{
			devicemanager::ScreenManager::getInstance().putchar(c);
		}

		static void	putstr(const char* str)
		{
			for(int i = 0; str[i] != '\0'; ++i)
				putchar(str[i]);
		}

		static void	printf_unsigned_long(unsigned long number, int radix)
		{
			char buffer[32];
			int pos = 0;

			do
			{
				unsigned long rem = number % radix;
				number /= radix;
				buffer[pos++] = HEX_CHARS[rem];
			} while (number > 0);

			while (--pos >= 0)
				putchar(buffer[pos]);
		}

		static void	printf_signed_long(long number, int radix)
		{
			if (number < 0)
			{
				putchar('-');
				printf_unsigned_long(-number, radix);
			}
			else
				printf_unsigned_long(number, radix);
		}

		static unsigned long long	custom_divide_64bit(unsigned long long numerator, int denominator, int *remainder)
		{
			unsigned long long quotient = 0;
			int temp = 0;

			for (int i = 63; i >= 0; i--)
			{
				temp = (temp << 1) | ((numerator >> i) & 1);
				if (temp >= denominator) {
					temp -= denominator;
					quotient = (quotient << 1) | 1;
				} 
				else
					quotient <<= 1;
			}

			if (remainder)
				*remainder = temp;

			return quotient;
		}

		static void	printf_unsigned_long_long(unsigned long long number, int radix)
		{
			char buffer[64];
			int pos = 0;

			do 
			{
				int rem;
				unsigned long long tmp = custom_divide_64bit(number, radix, &rem);
				buffer[pos++] = HEX_CHARS[rem];
				number = tmp;
			} while (number > 0);

			while (--pos >= 0)
				putchar(buffer[pos]);
		}

		static void	printf_signed_long_long(long long number, int radix)
		{
			if (number < 0)
			{
				putchar('-');
				printf_unsigned_long_long(-number, radix);
			}
			else
				printf_unsigned_long_long(number, radix);
		}

	} // namespace

		void	printf(const char* fmt, ...)
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
								putchar(*fmt);
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
							putchar((char)va_arg(args, int));
							break;
						case 's':
							putstr(va_arg(args, const char*));
							break;
						case '%':
							putchar('%');
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
									printf_signed_long_long(va_arg(args, long long), radix);
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
									printf_unsigned_long_long(va_arg(args, unsigned long long), radix);
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

	} // namespace common

} // namespace crowos
