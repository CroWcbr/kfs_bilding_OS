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
			virtual void OnMouseDown(uint8 button);
			virtual void OnMouseUp(uint8 button);
			virtual void OnMouseMove(int8 x, int8 y);
		};

		class MouseDriver : public hardware::InterruptHandler, public Driver
		{
			hardware::Port8bit dataport;
			hardware::Port8bit commandport;

			uint8 buffer[3];
			uint8 offset;
			uint8 buttons;

			MouseEventHandler* handler;

		public:
			MouseDriver(hardware::InterruptManager* manager, MouseEventHandler *handler);
			~MouseDriver();

			virtual uint32 HandleInterrupt(uint32 esp);
			virtual void Activate();
		};

	} // namespace drivers

} // namespace crowos

#endif
