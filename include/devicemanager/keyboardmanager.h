#ifndef __CROW__KEYBOARDMANAGER_H
#define __CROW__KEYBOARDMANAGER_H

#include <common/types.h>
#include <drivers/keyboard.h>
#include <devicemanager/screenmanager.h>

namespace crowos
{
	namespace devicemanager
	{
		class PrintfKeyboardEventHandler : public drivers::KeyboardEventHandler
		{
		private:	

		private:
			ScreenManager*	my_screen;
			int8			key_shift;
			// int8			key_ctrl;
			bool			key_caps;
			bool			qwerty_layout;

		private:
			void OnKeyDown(uint8 key);
			void OnKeyUp(uint8 key);
			void chooseKeyLetterLayout(char key[4]);
			void chooseKeyLetter(char key[2]);

		public:
			PrintfKeyboardEventHandler();
		};

	} // namespace devicemanager

} // namespace crowos

#endif
