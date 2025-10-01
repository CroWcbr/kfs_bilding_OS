#include <drivers/driver.h>

namespace crowos::drivers
{

Driver::Driver()
{
}

void Driver::Activate()
{

}

int Driver::Reset()
{
	return 0;
}

void Driver::Deactivate()
{

}

DriverManager::DriverManager()
{
	numDrivers = 0;
}

void DriverManager::AddDriver(Driver* drv)
{
	drivers[numDrivers] = drv;
	numDrivers++;
}

void DriverManager::ActivateAll()
{
	for (int i = 0; i < numDrivers; ++i)
		drivers[i]->Activate();
}

} // crowos::drivers
