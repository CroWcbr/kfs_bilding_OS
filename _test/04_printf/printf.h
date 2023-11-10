#ifndef __CROWOS__PRINTF_H
#define __CROWOS__PRINTF_H

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

const char g_HexChars[] = "0123456789abcdef";

typedef char int8_t;
typedef unsigned char uint8_t;

typedef short int16_t;
typedef unsigned short uint16_t;

typedef int int32_t;
typedef unsigned int uint32_t;

typedef long long int int64_t;
typedef unsigned long long int uint64_t;

void my_putc(char c);
void my_puts(char* str);
extern "C" void my_printf(const char *fmt, ...);

#endif
