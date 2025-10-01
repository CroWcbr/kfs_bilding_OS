#include <hardware/interrupts.h>
#include <common/stdio.h>

namespace crowos::hardware
{

InterruptHandler::InterruptHandler(uint8 interruptNumber, InterruptManager* interruptManager)
{
	this->interruptNumber = interruptNumber;
	this->interruptManager = interruptManager;
	interruptManager->handlers[interruptNumber] = this;
}

InterruptHandler::InterruptHandler()
{
	if (interruptManager->handlers[interruptNumber] == this)
		interruptManager->handlers[interruptNumber] = 0;
}

uint32 InterruptHandler::HandleInterrupt(uint32 esp)
{
	return esp;
}

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];
InterruptManager* InterruptManager::ActivateInterruptManager = 0;

void InterruptManager::SetIterruptDescriptorTable(
		uint8 interruptNumber,
		uint16 gdt_codeSegmentSelectorOffset,
		void (*handler)(),
		uint8 DescriptorPrivilegeLevel,
		uint8 DescriptorType)
{
	const uint8 IDT_DESC_PRESENT = 0x80;
	interruptDescriptorTable[interruptNumber].handlerAddresLowBits = ((uint32)handler) & 0xFFFF;
	interruptDescriptorTable[interruptNumber].handlerAddresHighBits = (((uint32)handler) >> 16) & 0xFFFF;
	interruptDescriptorTable[interruptNumber].gdt_codeSegmentSelector = gdt_codeSegmentSelectorOffset;
	interruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | DescriptorType | ((DescriptorPrivilegeLevel & 3) << 5);
	interruptDescriptorTable[interruptNumber].reserved = 0;
}

InterruptManager::InterruptManager(GlobalDescriptorTable* gdt)
: picMasterCommand(0x20)
, picMasterData(0x21)
, picSlaveCommand(0xA0)
, picSlaveData(0xA1)
{
	uint16 CodeSegment = gdt->CodeSegmentSelector();
	const uint8 IDT_INTERRUPT_GATE = 0xE;
	for (uint16 i = 0; i < 256; ++i)
	{
		handlers[i] = 0;
		SetIterruptDescriptorTable(i, CodeSegment, &IgnoreInterruptRequest, 0, IDT_INTERRUPT_GATE);
	}

	SetIterruptDescriptorTable(0x00, CodeSegment, &HandleException0x00, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x00, CodeSegment, &HandleException0x00, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x01, CodeSegment, &HandleException0x01, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x02, CodeSegment, &HandleException0x02, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x03, CodeSegment, &HandleException0x03, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x04, CodeSegment, &HandleException0x04, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x05, CodeSegment, &HandleException0x05, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x06, CodeSegment, &HandleException0x06, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x07, CodeSegment, &HandleException0x07, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x08, CodeSegment, &HandleException0x08, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x09, CodeSegment, &HandleException0x09, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x0A, CodeSegment, &HandleException0x0A, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x0B, CodeSegment, &HandleException0x0B, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x0C, CodeSegment, &HandleException0x0C, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x0D, CodeSegment, &HandleException0x0D, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x0E, CodeSegment, &HandleException0x0E, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x0F, CodeSegment, &HandleException0x0F, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x10, CodeSegment, &HandleException0x10, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x11, CodeSegment, &HandleException0x11, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x12, CodeSegment, &HandleException0x12, 0, IDT_INTERRUPT_GATE);
    SetIterruptDescriptorTable(0x13, CodeSegment, &HandleException0x13, 0, IDT_INTERRUPT_GATE);

	SetIterruptDescriptorTable(0x20, CodeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
	SetIterruptDescriptorTable(0x21, CodeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);
	SetIterruptDescriptorTable(0x22, CodeSegment, &HandleInterruptRequest0x02, 0, IDT_INTERRUPT_GATE);
	SetIterruptDescriptorTable(0x23, CodeSegment, &HandleInterruptRequest0x03, 0, IDT_INTERRUPT_GATE);
	SetIterruptDescriptorTable(0x24, CodeSegment, &HandleInterruptRequest0x04, 0, IDT_INTERRUPT_GATE);
	SetIterruptDescriptorTable(0x25, CodeSegment, &HandleInterruptRequest0x05, 0, IDT_INTERRUPT_GATE);
	SetIterruptDescriptorTable(0x26, CodeSegment, &HandleInterruptRequest0x06, 0, IDT_INTERRUPT_GATE);
	SetIterruptDescriptorTable(0x27, CodeSegment, &HandleInterruptRequest0x07, 0, IDT_INTERRUPT_GATE);
	SetIterruptDescriptorTable(0x28, CodeSegment, &HandleInterruptRequest0x08, 0, IDT_INTERRUPT_GATE);
	SetIterruptDescriptorTable(0x29, CodeSegment, &HandleInterruptRequest0x09, 0, IDT_INTERRUPT_GATE);
	SetIterruptDescriptorTable(0x2A, CodeSegment, &HandleInterruptRequest0x0A, 0, IDT_INTERRUPT_GATE);
	SetIterruptDescriptorTable(0x2B, CodeSegment, &HandleInterruptRequest0x0B, 0, IDT_INTERRUPT_GATE);
	SetIterruptDescriptorTable(0x2C, CodeSegment, &HandleInterruptRequest0x0C, 0, IDT_INTERRUPT_GATE);
	SetIterruptDescriptorTable(0x2D, CodeSegment, &HandleInterruptRequest0x0D, 0, IDT_INTERRUPT_GATE);
	SetIterruptDescriptorTable(0x2E, CodeSegment, &HandleInterruptRequest0x0E, 0, IDT_INTERRUPT_GATE);
	SetIterruptDescriptorTable(0x2F, CodeSegment, &HandleInterruptRequest0x0F, 0, IDT_INTERRUPT_GATE);

	SetIterruptDescriptorTable(0x80, CodeSegment, &HandleInterruptRequest0x80, 0, IDT_INTERRUPT_GATE);

	picMasterCommand.Write(0x11);
	picSlaveCommand.Write(0x11);

	picMasterData.Write(0x20);
	picSlaveData.Write(0x28);

	picMasterData.Write(0x04);
	picSlaveData.Write(0x02);

	picMasterData.Write(0x01);
	picSlaveData.Write(0x01);

	picMasterData.Write(0x00);
	picSlaveData.Write(0x00);

	InterruptDescriptionTablePointer idt;
	idt.size = 256 * sizeof(GateDescriptor) - 1;
	idt.base = (uint32)interruptDescriptorTable;

	asm volatile("lidt %0" : : "m" (idt));
}

InterruptManager::~InterruptManager()
{
	Deactivate();
}

void InterruptManager::Activate()
{
	if(ActivateInterruptManager != 0)
		ActivateInterruptManager->Deactivate();
	ActivateInterruptManager = this;
	asm("sti");
}

void InterruptManager::Deactivate()
{
	if(ActivateInterruptManager == this)
	{
		ActivateInterruptManager = 0;
		asm("cli");
	}
}

uint32 InterruptManager::handleInterrupt(uint8 interruptNumber, uint32 esp)
{
	if (ActivateInterruptManager != 0)
		return ActivateInterruptManager->DoHandleInterrupt(interruptNumber, esp);
	return esp;
}

void InterruptManager::clean_all_registers()
{
    asm volatile (
        "xor %eax, %eax \n\t"
        "xor %ebx, %ebx \n\t"
        "xor %ecx, %ecx \n\t"
        "xor %edx, %edx \n\t"
        "xor %esi, %esi \n\t"
        "xor %edi, %edi \n\t"
        "xor %ebp, %ebp \n\t"
    );
}

void InterruptManager::isr_handler(uint8 interruptNumber)
{
	printf("Interrupt Service Routine handler ");
	if (interruptNumber < 16)
		printf("0x0%p\n", interruptNumber);
	else
		printf("0x%p\n", interruptNumber);

	switch (interruptNumber)
	{
		case 0x00: printf("Division by Zero\n"); break;
		case 0x01: printf("Debugger\n"); break;
		case 0x02: printf("NMI\n"); break;
		case 0x03: printf("Breakpoint\n"); break;
		case 0x04: printf("Overflow\n"); break;
		case 0x05: printf("Bounds\n"); break;
		case 0x06: printf("Invalid Opcode\n"); break;
		case 0x07: printf("Coprocessor not available\n"); break;
		case 0x08: printf("Double Fault\n"); break;
		case 0x09: printf("Coprocessor Segment Overrun (386 or earlier only)\n"); break;
		case 0x0A: printf("Invalid Task State Segment\n"); break;
		case 0x0B: printf("Segment not present\n"); break;
		case 0x0C: printf("Stack Fault\n"); break;
		case 0x0D: printf("General protection fault\n"); break;
		case 0x0E: printf("Page fault\n"); break;
		case 0x0F: printf("reserved\n"); break;
		case 0x10: printf("Math Fault\n"); break;
		case 0x11: printf("Alignment Check\n"); break;
		case 0x12: printf("Machine Check\n"); break;
		case 0x13: printf("SIMD Floating-Point Exception\n"); break;
		default: printf("unknown ISR code\n"); break;
	}
	uint32 esp;
	asm(" mov %%esp, %0" : "=r" (esp));
	printf("esp = 0x%x\n", esp);
	print_stack((uint8*)esp);
	printf("kernel panic\n");
	clean_all_registers();
	__asm__ ("hlt");
}

void InterruptManager::irq_handler(uint8 interruptNumber)
{
	printf("Interrupt Request handler ");
	if (interruptNumber < 16)
		printf("0x0%p\n", interruptNumber);
	else
		printf("0x%p\n", interruptNumber);
	switch (interruptNumber)
	{
		case 0x20: printf("Programmable Interrupt Timer Interrupt\n"); break;
		case 0x21: printf("Keyboard Interrupt\n"); break;
		case 0x22: printf("Cascade (used internally by the two PICs. never raised)\n"); break;
		case 0x23: printf("COM2 (if enabled)\n"); break;
		case 0x24: printf("COM1 (if enabled)\n"); break;
		case 0x25: printf("LPT2 (if enabled)\n"); break;
		case 0x26: printf("Floppy Disk\n"); break;
		case 0x27: printf("LPT1 / Unreliable \"spurious\" interrupt (usually)\n"); break;
		case 0x28: printf("CMOS real-time clock (if enabled)\n"); break;
		case 0x29: printf("Free for peripherals / legacy SCSI / NIC\n"); break;
		case 0x2A: printf("Free for peripherals / SCSI / NIC\n"); break;
		case 0x2B: printf("Free for peripherals / SCSI / NIC\n"); break;
		case 0x2C: printf("PS2 Mouse\n"); break;
		case 0x2D: printf("FPU / Coprocessor / Inter-processor\n"); break;
		case 0x2E: printf("Primary ATA Hard Disk\n"); break;
		case 0x2F: printf("Secondary ATA Hard Disk\n"); break;
		default : printf("unknown IRQ code\n"); break;
	}
}

uint32 InterruptManager::DoHandleInterrupt(uint8 interruptNumber, uint32 esp)
{
	if (handlers[interruptNumber] != 0)
	{
		// printf("DoHandleInterrupt %x\n", interruptNumber);
		// printf("esp1 %d\n", interruptNumber);
		// printf("esp2 %x\n", interruptNumber);
		esp = handlers[interruptNumber]->HandleInterrupt(esp);
	}
	else if (interruptNumber != 0x20)
	{
		if (interruptNumber < 0x20)
			isr_handler(interruptNumber);
		else if (interruptNumber < 0x30)
			irq_handler(interruptNumber);
		else
			printf("unknown Interrupt code %x\n", interruptNumber);
	}

	if (0x20 <= interruptNumber && interruptNumber < 0x30)
	{
		picMasterCommand.Write(0x20);
		if (0x28 <= interruptNumber)
			picSlaveCommand.Write(0x20);
	}

	return esp;
}

} // namespace crowos::hardware