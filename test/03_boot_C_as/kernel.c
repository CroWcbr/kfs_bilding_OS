void print(const char* str)
{
	unsigned short* VideoMemory = (unsigned short*)0xb8000;

	int i = 0;
	while(str[i] != '\0')
	{
		VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
		i++;
	}
}

void clearScreen(unsigned char color)
{
	unsigned short* Screen = (unsigned short*)0xb8000;
	int i = 0;
	while(i < 80 * 25)
	{
		Screen[i] = (Screen[i] & 0xFF00) | ' ';
		i++;
	}
}

void kernelMain(void *multiboot_structure, unsigned int magicnumber)
{
	clearScreen(0x02);
	print("Hello World!");
}
