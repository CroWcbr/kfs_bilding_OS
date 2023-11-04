#include "stdio.h"

void putc(char c)
{

}



void printf(const char* fmt, ...)
{
	int* argp = (int*)&fmt;
	argp += sizeof(fmt) / sizeof(int);
	argp++;
	argp++;
	argp++;
}

int main()
{
	printf("Test %d %d %d %d", 1, 2, 3, 4);
	return 0;
}