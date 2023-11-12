#ifndef __CROW__MOUSEMANAGER_H
#define __CROW__MOUSEMANAGER_H

#include <drivers/mouse.h>
#include <vga/screen.h>
#include <common/types.h>

namespace crowos
{
	namespace devicemanager
	{

		class MouseToConsole : public crowos::drivers::MouseEventHandler
		{
		private:
			crowos::common::int8_t x;
			crowos::common::int8_t y;

		public:
			MouseToConsole();
			void OnMouseMove(int xoffset, int yoffset);
		};

	}

}

#endif
