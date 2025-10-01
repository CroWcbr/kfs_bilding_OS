#ifndef __CROW__MOUSEMANAGER_H
#define __CROW__MOUSEMANAGER_H

#include <drivers/mouse.h>
#include <vga/screen.h>
#include <common/types.h>
#include <devicemanager/screenmanager.h>

namespace crowos
{
	namespace devicemanager
	{

		class MouseToConsole : public drivers::MouseEventHandler
		{
		private:
			ScreenManager*	my_screen;
			int8			x;
			int8			y;

		public:
			MouseToConsole();
			void OnMouseMove(int8 xoffset, int8 yoffset);
		};

	} // namespace devicemanager

} // namespace crowos

#endif
