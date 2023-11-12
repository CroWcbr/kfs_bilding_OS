#ifndef __CROW__KEYBOARDMANAGER_H
#define __CROW__KEYBOARDMANAGER_H

#include <drivers/keyboard.h>
#include <devicemanager/screenmanager.h>

namespace crowos
{
	namespace devicemanager
	{

		class PrintfKeyboardEventHandler : public crowos::drivers::KeyboardEventHandler
		{
		private:
			ScreenManager*	my_screen;
			bool			shift;
			bool			ctrl;
			bool			tab;

		private:
			void OnKeyDown(char c);
			void OnKeyUp(char c);
		
		public:
			PrintfKeyboardEventHandler();
		};

	}

}

#endif
