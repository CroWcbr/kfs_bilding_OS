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

			virtual void OnKeyDown(char);
			virtual void OnKeyUp(char);
		};

		class KeyboardDriver : public crowos::hardware::InterruptHandler, public Driver
		{
			crowos::hardware::Port8bit dataport;
			crowos::hardware::Port8bit commandport;

			KeyboardEventHandler* handler;

		public:
			KeyboardDriver(crowos::hardware::InterruptManager* manager, KeyboardEventHandler *handler);
			~KeyboardDriver();

			virtual crowos::common::uint32_t HandleInterrupt(crowos::common::uint32_t esp);
			virtual void Activate();
		};
	}
}
#endif
