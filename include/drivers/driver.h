#ifndef __CROWOS__DRIVER_H
#define __CROWOS__DRIVER_H

#include "common/types.h"

namespace crowos
{
	namespace drivers
	{
		class Driver
		{
		public:
			Driver();

			virtual void Activate();
			virtual int32 Reset();
			virtual void Deactivate();
		};

		class DriverManager
		{
		private:
			Driver *drivers[2]; // keyboard, mouse
			int32 numDrivers;

		public:
			DriverManager();

			void AddDriver(Driver* drv);
			void ActivateAll();

		};

	} // namespace drivers

} //namespace crowos

#endif
