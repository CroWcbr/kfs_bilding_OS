#ifndef __CROW__KEYBOARDMANAGER_H
#define __CROW__KEYBOARDMANAGER_H

#include <common/types.h>
#include <drivers/keyboard.h>
#include <devicemanager/screenmanager.h>

namespace crowos
{
	namespace devicemanager
	{

		#define MAX_SCAN_CODE 0x80	//128

		class PrintfKeyboardEventHandler : public crowos::drivers::KeyboardEventHandler
		{
		private:	
			struct key_code
			{
				char qwerty;
				char shift_qwerty;
				char azerty;
				char shift_azerty;
			};

			key_code scan_codes[MAX_SCAN_CODE];

		private:
			ScreenManager*	my_screen;

		private:
			crowos::common::int8_t			shift;
			crowos::common::int8_t			ctrl;
			crowos::common::int8_t			tab;

		private:
			void OnKeyDown(crowos::common::uint8_t key);
			void OnKeyUp(crowos::common::uint8_t key);
		
		public:
			PrintfKeyboardEventHandler();
		};

	}

}

#endif
