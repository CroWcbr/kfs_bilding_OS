#include <drivers/keyboard.h>
#include <common/stdio.h>

using namespace crowos::common;
using namespace crowos::drivers;
using namespace crowos::hardware;

KeyboardEventHandler::KeyboardEventHandler()
{}

void KeyboardEventHandler::OnKeyDown(uint8_t)
{}

void KeyboardEventHandler::OnKeyUp(uint8_t)
{}

KeyboardDriver::KeyboardDriver(InterruptManager* manager, KeyboardEventHandler *handler)
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
	uint8_t status = (dataport.Read() | 1) & ~0x10;
	commandport.Write(0x60);
	dataport.Write(status);

	dataport.Write(0xF4);
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
	uint8_t key = dataport.Read();

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
