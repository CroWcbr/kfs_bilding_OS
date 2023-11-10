#include "printf.h"
#include <unistd.h>
#include "my_stdarg.h"

void my_putc(char c)
{
	write(1, &c, 1);
}

void my_puts(const char* str)
{
	while (*str)
	{
		my_putc(*str);
		str++;
	}
}

void printf_unsigned(uint64_t number, int radix)
{
	char buffer[32];
	int pos = 0;

	do 
	{
		unsigned long long rem = number % radix;
		number /= radix;
		buffer[pos++] = g_HexChars[rem];
	} while (number > 0);

	while (--pos >= 0)
		my_putc(buffer[pos]);
}

void printf_signed(int64_t number, int radix)
{
	if (number < 0)
	{
		my_putc('-');
		printf_unsigned(-number, radix);
	}
	else
		printf_unsigned(number, radix);
}

void my_printf(const char* fmt, ...)
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
						my_putc(*fmt);
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
					my_putc((char)va_arg(args, int));
					break;
				case 's':
					my_puts(va_arg(args, const char*));
					break;
				case '%':
					my_putc('%');
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
							printf_signed(va_arg(args, int), radix);
							break;

						case PRINTF_LENGTH_LONG:
							printf_signed(va_arg(args, long), radix);
							break;

						case PRINTF_LENGTH_LONG_LONG:
							printf_signed(va_arg(args, long long), radix);
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
							printf_unsigned(va_arg(args, unsigned int), radix);
							break;

						case PRINTF_LENGTH_LONG:
							printf_unsigned(va_arg(args, unsigned  long), radix);
							break;

						case PRINTF_LENGTH_LONG_LONG:
							printf_unsigned(va_arg(args, unsigned  long long), radix);
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

int main()
{
	my_printf("Test\n %lld\n %llu\n %d\n %d\n", 4294967295 , 4294967296, 3, 4);
	return 0;
}
