#include <devicemanager/keyboardmanager.h>
#include <common/stdio.h>

using namespace crowos::devicemanager;
using namespace crowos::common;

PrintfKeyboardEventHandler::PrintfKeyboardEventHandler()
{
	my_screen = &(ScreenManager::getInstance());
	shift = false;
	ctrl = false;
	tab = false;
}

void PrintfKeyboardEventHandler::OnKeyDown(char key)
{
	switch (key)
	{
//keyboard zero row - only used
		case 0x3b: my_screen->ChangeDisplay(0); break;	//F1
		case 0x3c: my_screen->ChangeDisplay(1); break;	//F2
		case 0x3d: my_screen->ChangeDisplay(2); break;	//F3

//keyboard first row
		case 0x29: my_screen->putchar('`'); break;
		case 0x02: my_screen->putchar('1'); break;
		case 0x03: my_screen->putchar('2'); break;
		case 0x04: my_screen->putchar('3'); break;
		case 0x05: my_screen->putchar('4'); break;
		case 0x06: my_screen->putchar('5'); break;
		case 0x07: my_screen->putchar('6'); break;
		case 0x08: my_screen->putchar('7'); break;
		case 0x09: my_screen->putchar('8'); break;
		case 0x0A: my_screen->putchar('9'); break;
		case 0x0B: my_screen->putchar('0'); break;
		case 0x0C: my_screen->putchar('-'); break;
		case 0x0D: my_screen->putchar('='); break;
		case 0x0E: my_screen->putchar('\b'); break;	//backspace
//keyboard second row
		case 0x0F: my_screen->putchar('\t'); break;	//tab
		case 0x10: my_screen->putchar('q'); break;
		case 0x11: my_screen->putchar('w'); break;
		case 0x12: my_screen->putchar('e'); break;
		case 0x13: my_screen->putchar('r'); break;
		case 0x14: my_screen->putchar('t'); break;
		case 0x15: my_screen->putchar('y'); break;
		case 0x16: my_screen->putchar('u'); break;
		case 0x17: my_screen->putchar('i'); break;
		case 0x18: my_screen->putchar('o'); break;
		case 0x19: my_screen->putchar('p'); break;
		case 0x1A: my_screen->putchar('['); break;
		case 0x1B: my_screen->putchar(']'); break;
		case 0x2B: my_screen->putchar('\\'); break;
		case 0x1C: //enter
			my_screen->putchar('\n');
			//check command? i think here....
			my_screen->print_shell_promt();
			break;
//keyboard third row
		//CAPS missed
		case 0x1E: my_screen->putchar('a'); break;
		case 0x1F: my_screen->putchar('s'); break;
		case 0x20: my_screen->putchar('d'); break;
		case 0x21: my_screen->putchar('f'); break;
		case 0x22: my_screen->putchar('g'); break;
		case 0x23: my_screen->putchar('h'); break;
		case 0x24: my_screen->putchar('j'); break;
		case 0x25: my_screen->putchar('k'); break;
		case 0x26: my_screen->putchar('l'); break;
		case 0x27: my_screen->putchar(';'); break;
		case 0x28: my_screen->putchar('\''); break;
//keyboard fourth row
		//SHIFT missed
		case 0x2C: my_screen->putchar('z'); break;
		case 0x2D: my_screen->putchar('x'); break;
		case 0x2E: my_screen->putchar('c'); break;
		case 0x2F: my_screen->putchar('v'); break;
		case 0x30: my_screen->putchar('b'); break;
		case 0x31: my_screen->putchar('n'); break;
		case 0x32: my_screen->putchar('m'); break;
		case 0x33: my_screen->putchar(','); break;
		case 0x34: my_screen->putchar('.'); break;
		case 0x35: my_screen->putchar('/'); break;
		//SHIFT missed

//keyboard fifth row - only used
		case 0x39: my_screen->putchar(' '); break;	//space
		// CAPS
		// SHIFT
		// CTRL
		// case 0x2A: case 0x36:
		// 	printk("shift = true\n");
		// 	my_screen->putchar();
		// 	shift = 1;
		// 	break;
		// case 0xAA: case 0xB6:
		// 	printk("shift = false\n");
		// 	shift = 0;
		// 	break;

		// default: //print all for test!
		// 	printf("\nKEYBOARD OnKeyDown 0x%X\n", key);
		// 	break;
	}

}

void PrintfKeyboardEventHandler::OnKeyUp(char c)
{
	// default: //print all for test!
	// 	printf("\nKEYBOARD OnKeyUp 0x%X\n", key);
}
