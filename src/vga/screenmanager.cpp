#include <vga/screenmanager.h>

using namespace crowos::vga;

ScreenManager& ScreenManager::getInstance()
{
	static ScreenManager instance;
	static bool initialized = false;
	if (!initialized)
	{
		instance.my_screen = &(Screen::getInstance());
		initialized = true;
	}
	return instance;
}

void	ScreenManager::putchar(char c)
{
	my_screen->putchar(c);
}

void	ScreenManager::putstr(const char* str)
{
	for(int i = 0; str[i] != '\0'; ++i)
		putchar(str[i]);
}

void	ScreenManager::printf_unsigned_long(unsigned long number, int radix)
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
		putchar(buffer[pos]);
}

void	ScreenManager::printf_signed_long(long number, int radix)
{
	if (number < 0)
	{
		putchar('-');
		printf_unsigned_long(-number, radix);
	}
	else
		printf_unsigned_long(number, radix);
}

unsigned long long	ScreenManager::custom_divide_64bit(unsigned long long numerator, int denominator, int *remainder)
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

void	ScreenManager::printf_unsigned_long_long(unsigned long long number, int radix)
{
	char buffer[64];
	int pos = 0;

	do 
	{
		int rem;
		unsigned long long tmp = custom_divide_64bit(number, radix, &rem);
		buffer[pos++] = g_HexChars[rem];
		number = tmp;
	} while (number > 0);

	while (--pos >= 0)
		putchar(buffer[pos]);
}

void	ScreenManager::printf_signed_long_long(long long number, int radix)
{
	if (number < 0)
	{
		putchar('-');
		printf_unsigned_long_long(-number, radix);
	}
	else
		printf_unsigned_long_long(number, radix);
}
