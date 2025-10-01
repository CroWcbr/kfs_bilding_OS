#ifndef __CROWOS__KEYBOARD_H
#define __CROWOS__KEYBOARD_H

#include <common/types.h>
#include <hardware/interrupts.h>
#include <drivers/driver.h>
#include <hardware/port.h>

namespace crowos
{
	namespace drivers
	{
		class KeyboardEventHandler
		{
		public:
			KeyboardEventHandler();

			virtual void OnKeyDown(uint8);
			virtual void OnKeyUp(uint8);
		};

		class KeyboardDriver : public hardware::InterruptHandler, public Driver
		{
			hardware::Port8bit dataport;
			hardware::Port8bit commandport;

			KeyboardEventHandler* handler;

		public:
			KeyboardDriver(hardware::InterruptManager* manager, KeyboardEventHandler *handler);
			~KeyboardDriver();

			virtual uint32 HandleInterrupt(uint32 esp);
			virtual void Activate();
		};

	} // namespace drivers

} // namespace crowos

#endif
