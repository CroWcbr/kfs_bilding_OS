#include <devicemanager/keyboardmanager.h>
#include <common/stdio.h>

using namespace crowos::devicemanager;
using namespace crowos::common;

PrintfKeyboardEventHandler::PrintfKeyboardEventHandler()
{
	my_screen = &(ScreenManager::getInstance());

	key_shift = 0;
	key_caps = false;
	qwerty_layout = true;
}

void PrintfKeyboardEventHandler::chooseKeyLetterLayout(char key[4])
{
	int pos = (qwerty_layout ? 0 : 2) + (key_caps ? (key_shift ? 0 : 1) : (key_shift ? 1 : 0));
	my_screen->putchar(key[pos]);
}

void PrintfKeyboardEventHandler::chooseKeyLetter(char key[2])
{
	int pos = (key_caps ? (key_shift ? 0 : 1) : (key_shift ? 1 : 0));
	my_screen->putchar(key[pos]);
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
		case 0x10: chooseKeyLetterLayout("qQaA"); break;
		case 0x11: chooseKeyLetterLayout("wWzZ"); break;
		case 0x12: chooseKeyLetter("eE"); break;
		case 0x13: chooseKeyLetter("rR"); break;
		case 0x14: chooseKeyLetter("tT"); break;
		case 0x15: chooseKeyLetter("yY"); break;
		case 0x16: chooseKeyLetter("uU"); break;
		case 0x17: chooseKeyLetter("iI"); break;
		case 0x18: chooseKeyLetter("oO"); break;
		case 0x19: chooseKeyLetter("pP"); break;
		case 0x1A: my_screen->putchar(key_shift ? '{' :'['); break;
		case 0x1B: my_screen->putchar(key_shift ? '}' :']'); break;
		case 0x2B: my_screen->putchar(key_shift ? '|' :'\\'); break;
		case 0x1C: //enter
			my_screen->check_command();
			my_screen->print_shell_promt();
			break;
//keyboard third row
		//CAPS missed
		case 0x1E: chooseKeyLetterLayout("aAqQ"); break;
		case 0x1F: chooseKeyLetter("sS"); break;
		case 0x20: chooseKeyLetter("dD"); break;
		case 0x21: chooseKeyLetter("fF"); break;
		case 0x22: chooseKeyLetter("gG"); break;
		case 0x23: chooseKeyLetter("hH"); break;
		case 0x24: chooseKeyLetter("jJ"); break;
		case 0x25: chooseKeyLetter("kK"); break;
		case 0x26: chooseKeyLetter("lL"); break;
		case 0x27: my_screen->putchar(key_shift ? ':' : ';'); break;
		case 0x28: my_screen->putchar(key_shift ? '\"' : '\''); break;
//keyboard fourth row
		case 0x2A: ++key_shift; break;
		case 0x2C: chooseKeyLetterLayout("zZwW"); break;
		case 0x2D: chooseKeyLetter("xX"); break;
		case 0x2E: chooseKeyLetter("cC"); break;
		case 0x2F: chooseKeyLetter("vV"); break;
		case 0x30: chooseKeyLetter("bB"); break;
		case 0x31: chooseKeyLetter("nN"); break;
		case 0x32: chooseKeyLetter("mM"); break;
		case 0x33: my_screen->putchar(key_shift ? '<' : ','); break;
		case 0x34: my_screen->putchar(key_shift ? '>' : '.'); break;
		case 0x35: my_screen->putchar(key_shift ? '?' : '/'); break;
		case 0x36: ++key_shift; break;

//keyboard fifth row - only used
		case 0x39: my_screen->putchar(' '); break;	//space

		case 0x3A: key_caps ? key_caps = false : key_caps = true;; break;
		// case 0x1D: ++key_ctrl; break;

		default: //print all for test!
			// printf("\nKEYBOARD OnKeyDown 0x%X\n", key);
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
		
		default: //print all for test!
		// 	printf("\nKEYBOARD OnKeyUp 0x%X\n", key);
			break;
	}
}
