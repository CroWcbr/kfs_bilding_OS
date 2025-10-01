#include <drivers/keyboard.h>
#include <common/stdio.h>

namespace crowos::drivers
{

KeyboardEventHandler::KeyboardEventHandler()
{}

void KeyboardEventHandler::OnKeyDown(uint8)
{}

void KeyboardEventHandler::OnKeyUp(uint8)
{}

KeyboardDriver::KeyboardDriver(hardware::InterruptManager* manager, KeyboardEventHandler *handler)
: InterruptHandler(0x21, manager)
, dataport(0x60)
, commandport(0x64)
{
	this->handler = handler;
}

void KeyboardDriver::Activate()
{
	while(commandport.Read() & 0x1)
		dataport.Read();

	commandport.Write(0xAE);
	commandport.Write(0x20);
	uint8 status = (dataport.Read() | 1) & ~0x10;
	commandport.Write(0x60);
	dataport.Write(status);

	dataport.Write(0xF4);
}

uint32 KeyboardDriver::HandleInterrupt(uint32 esp)
{
	uint8 key = dataport.Read();

	// printf("\nHandleInterrupt 0x%X\n", key);

	if(handler == 0)
		return esp;

	if (key == 0xFA)
		;
	else if (key > 0x80)
		handler->OnKeyUp(key);
	else
		handler->OnKeyDown(key);

	return esp;
}

} // namespace crowos::drivers