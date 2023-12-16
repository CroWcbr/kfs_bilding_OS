#include <devicemanager/keyboardmanager.h>
#include <common/stdio.h>

using namespace crowos::devicemanager;
using namespace crowos::common;

PrintfKeyboardEventHandler::PrintfKeyboardEventHandler()
{
	my_screen = &(ScreenManager::getInstance());

	key_shift = 0;
	qwerty_layout = true;
	// key_ctrl = 0;
	// key_caps = 0;
}

void PrintfKeyboardEventHandler::OnKeyDown(uint8_t key)
{
	switch (key)
	{
//keyboard zero row - only used
		case 0x3b: my_screen->ChangeDisplay(0); break;	//F1
		case 0x3c: my_screen->ChangeDisplay(1); break;	//F2
		case 0x3d: my_screen->ChangeDisplay(2); break;	//F3
		case 0x3e: qwerty_layout ? qwerty_layout = false : qwerty_layout = true; break;	//F3

//keyboard first row
		case 0x29: my_screen->putchar(key_shift ? '~' : '`'); break;
		case 0x02: my_screen->putchar(key_shift ? '!' : '1'); break;
		case 0x03: my_screen->putchar(key_shift ? '@' : '2'); break;
		case 0x04: my_screen->putchar(key_shift ? '#' : '3'); break;
		case 0x05: my_screen->putchar(key_shift ? '$' : '4'); break;
		case 0x06: my_screen->putchar(key_shift ? '%' : '5'); break;
		case 0x07: my_screen->putchar(key_shift ? '^' : '6'); break;
		case 0x08: my_screen->putchar(key_shift ? '&' : '7'); break;
		case 0x09: my_screen->putchar(key_shift ? '*' : '8'); break;
		case 0x0A: my_screen->putchar(key_shift ? '(' : '9'); break;
		case 0x0B: my_screen->putchar(key_shift ? ')' : '0'); break;
		case 0x0C: my_screen->putchar(key_shift ? '_' : '-'); break;
		case 0x0D: my_screen->putchar(key_shift ? '+' : '='); break;
		case 0x0E: my_screen->putchar('\b'); break;	//backspace
//keyboard second row
		case 0x0F: my_screen->putchar('\t'); break;	//tab
		case 0x10: 
			my_screen->putchar(key_shift ? qwerty_layout ? 'Q' : 'A' : qwerty_layout ? 'q' : 'a');
			break;
		case 0x11:
			my_screen->putchar(key_shift ? qwerty_layout ? 'W' : 'Z' : qwerty_layout ? 'w' : 'z');
			break;
		case 0x12: my_screen->putchar(key_shift ? 'E' : 'e'); break;
		case 0x13: my_screen->putchar(key_shift ? 'R' : 'r'); break;
		case 0x14: my_screen->putchar(key_shift ? 'T' : 't'); break;
		case 0x15: my_screen->putchar(key_shift ? 'Y' : 'y'); break;
		case 0x16: my_screen->putchar(key_shift ? 'U' : 'u'); break;
		case 0x17: my_screen->putchar(key_shift ? 'I' : 'i'); break;
		case 0x18: my_screen->putchar(key_shift ? 'O' : 'o'); break;
		case 0x19: my_screen->putchar(key_shift ? 'P' : 'p'); break;
		case 0x1A: my_screen->putchar(key_shift ? '{' :'['); break;
		case 0x1B: my_screen->putchar(key_shift ? '}' :']'); break;
		case 0x2B: my_screen->putchar(key_shift ? '|' :'\\'); break;
		case 0x1C: //enter
			my_screen->check_command();
			my_screen->print_shell_promt();
			break;
//keyboard third row
		//CAPS missed
		case 0x1E:
			my_screen->putchar(key_shift ? qwerty_layout ? 'A' : 'Q' : qwerty_layout ? 'a' : 'q');
			break;
		case 0x1F: my_screen->putchar(key_shift ? 'S' : 's'); break;
		case 0x20: my_screen->putchar(key_shift ? 'D' : 'd'); break;
		case 0x21: my_screen->putchar(key_shift ? 'F' : 'f'); break;
		case 0x22: my_screen->putchar(key_shift ? 'G' : 'g'); break;
		case 0x23: my_screen->putchar(key_shift ? 'H' : 'h'); break;
		case 0x24: my_screen->putchar(key_shift ? 'J' : 'j'); break;
		case 0x25: my_screen->putchar(key_shift ? 'K' : 'k'); break;
		case 0x26: my_screen->putchar(key_shift ? 'L' : 'l'); break;
		case 0x27: my_screen->putchar(key_shift ? ':' : ';'); break;
		case 0x28: my_screen->putchar(key_shift ? '\"' : '\''); break;
//keyboard fourth row
		case 0x2A: ++key_shift; break;
		case 0x2C:
			my_screen->putchar(key_shift ? qwerty_layout ? 'Z' : 'W' : qwerty_layout ? 'z' : 'w');
			break;
		case 0x2D: my_screen->putchar(key_shift ? 'X' : 'x'); break;
		case 0x2E: my_screen->putchar(key_shift ? 'C' : 'c'); break;
		case 0x2F: my_screen->putchar(key_shift ? 'V' : 'v'); break;
		case 0x30: my_screen->putchar(key_shift ? 'B' : 'b'); break;
		case 0x31: my_screen->putchar(key_shift ? 'N' : 'n'); break;
		case 0x32: my_screen->putchar(key_shift ? 'M' : 'm'); break;
		case 0x33: my_screen->putchar(key_shift ? '<' : ','); break;
		case 0x34: my_screen->putchar(key_shift ? '>' : '.'); break;
		case 0x35: my_screen->putchar(key_shift ? '?' : '/'); break;
		case 0x36: ++key_shift; break;

//keyboard fifth row - only used
		case 0x39: my_screen->putchar(' '); break;	//space

		// case 0x3A: ++key_caps; break;
		// case 0x1D: ++key_ctrl; break;

		default: //print all for test!
			printf("\nKEYBOARD OnKeyDown 0x%X\n", key);
			break;
	}

}

void PrintfKeyboardEventHandler::OnKeyUp(uint8_t key)
{
	switch (key - 0x80) // the same code as KeyDown
	{
		case 0x2A: --key_shift; break;
		case 0x36: --key_shift; break;
		// case 0x3A: --key_caps; break;
		// case 0x1D: --key_ctrl; break;
		
		// default: //print all for test!
		// 	printf("\nKEYBOARD OnKeyUp 0x%X\n", key);
		// 	break;
	}
}
