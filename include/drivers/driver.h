#ifndef __CROWOS__DRIVER_H
#define __CROWOS__DRIVER_H

namespace crowos
{
	namespace drivers
	{
		class Driver
		{
		public:
			Driver();

			virtual void Activate();
			virtual int Reset();
			virtual void Deactivate();
		};

		class DriverManager
		{
		private:
			Driver *drivers[2]; // keyboard, mouse
			int numDrivers;

		public:
			DriverManager();

			void AddDriver(Driver* drv);
			void ActivateAll();

		};
	}
}

#endif
