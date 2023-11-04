#ifndef __CROWOS__MOUSE_H
#define __CROWOS__MOUSE_H

#include <common/types.h>
#include <drivers/driver.h>
#include <hardware/interrupts.h>
#include <hardware/port.h>

namespace crowos
{
	namespace drivers
	{
		class MouseEventHandler
		{
		public:
			MouseEventHandler();

			virtual void OnActivate();
			virtual void OnMouseDown(crowos::common::uint8_t button);
			virtual void OnMouseUp(crowos::common::uint8_t button);
			virtual void OnMouseMove(int x, int y);
		};

		class MouseDriver : public crowos::hardware::InterruptHandler, public Driver
		{
			crowos::hardware::Port8bit dataport;
			crowos::hardware::Port8bit commandport;

			crowos::common::uint8_t buffer[3];
			crowos::common::uint8_t offset;
			crowos::common::uint8_t buttons;

			MouseEventHandler* handler;

		public:
			MouseDriver(crowos::hardware::InterruptManager* manager, MouseEventHandler *handler);
			~MouseDriver();

			virtual crowos::common::uint32_t HandleInterrupt(crowos::common::uint32_t esp);
			virtual void Activate();
		};
	}
}
#endif
