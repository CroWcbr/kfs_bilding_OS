#ifndef __CROW__KEYBOARDMANAGER_H
#define __CROW__KEYBOARDMANAGER_H

#include <common/types.h>
#include <drivers/keyboard.h>
#include <devicemanager/screenmanager.h>

namespace crowos
{
	namespace devicemanager
	{
		class PrintfKeyboardEventHandler : public crowos::drivers::KeyboardEventHandler
		{
		private:	

		private:
			ScreenManager*	my_screen;
			crowos::common::int8_t			key_shift;
			// crowos::common::int8_t			key_ctrl;
			// crowos::common::int8_t			key_caps;
			bool							qwerty_layout;

		private:
			void OnKeyDown(crowos::common::uint8_t key);
			void OnKeyUp(crowos::common::uint8_t key);
		
		public:
			PrintfKeyboardEventHandler();
		};

	}

}

#endif
