#ifndef __CROWOS__INTERRUPTS_H
#define __CROWOS__INTERRUPTS_H

#include <gdt.h>
#include <common/types.h>
#include <hardware/port.h>

namespace crowos
{
	namespace hardware
	{
		class InterruptManager;

		class InterruptHandler
		{
		protected:
			uint8 interruptNumber;
			InterruptManager* interruptManager;

			InterruptHandler(uint8 interruptNumber, InterruptManager* interruptManager);
			InterruptHandler();
		public:
			virtual uint32 HandleInterrupt(uint32 esp);
		};

		class InterruptManager
		{
		friend class InterruptHandler;
		protected:

			static InterruptManager* ActivateInterruptManager;
			InterruptHandler* handlers[256];

			struct GateDescriptor
			{
				uint16	handlerAddresLowBits;
				uint16	gdt_codeSegmentSelector;
				uint8	reserved;
				uint8	access;
				uint16	handlerAddresHighBits;
			} __attribute__((packed));

			static GateDescriptor interruptDescriptorTable[256];

			struct InterruptDescriptionTablePointer
			{
				uint16	size;
				uint32	base;
			} __attribute__((packed));

			static void SetIterruptDescriptorTable(
				uint8 interruptNumber,
				uint16 gdt_codeSegmentSelectorOffset,
				void (*handler)(),
				uint8 DescriptorPrivilegeLevel,
				uint8 DescriptorType);

			Port8bitSlow	picMasterCommand;
			Port8bitSlow	picMasterData;
			Port8bitSlow	picSlaveCommand;
			Port8bitSlow	picSlaveData;

			static uint32	handleInterrupt(uint8 interruptNumber, uint32 esp);
			uint32			DoHandleInterrupt(uint8 interruptNumber, uint32 esp);
			void			isr_handler(uint8 interruptNumber);
			void			irq_handler(uint8 interruptNumber);
			void			clean_all_registers();

			static void		IgnoreInterruptRequest();
			static void		HandleInterruptRequest0x00();
			static void		HandleInterruptRequest0x01();
			static void		HandleInterruptRequest0x02();
			static void		HandleInterruptRequest0x03();
			static void		HandleInterruptRequest0x04();
			static void		HandleInterruptRequest0x05();
			static void		HandleInterruptRequest0x06();
			static void		HandleInterruptRequest0x07();
			static void		HandleInterruptRequest0x08();
			static void		HandleInterruptRequest0x09();
			static void		HandleInterruptRequest0x0A();
			static void		HandleInterruptRequest0x0B();
			static void		HandleInterruptRequest0x0C();
			static void		HandleInterruptRequest0x0D();
			static void		HandleInterruptRequest0x0E();
			static void		HandleInterruptRequest0x0F();

			static void		HandleInterruptRequest0x80();

			static void		HandleException0x00();
			static void 	HandleException0x01();
			static void		HandleException0x02();
			static void		HandleException0x03();
			static void		HandleException0x04();
			static void		HandleException0x05();
			static void		HandleException0x06();
			static void		HandleException0x07();
			static void		HandleException0x08();
			static void		HandleException0x09();
			static void		HandleException0x0A();
			static void		HandleException0x0B();
			static void		HandleException0x0C();
			static void		HandleException0x0D();
			static void		HandleException0x0E();
			static void		HandleException0x0F();
			static void		HandleException0x10();
			static void		HandleException0x11();
			static void		HandleException0x12();
			static void		HandleException0x13();

		public:
			InterruptManager(GlobalDescriptorTable* gdt);
			~InterruptManager();

			void Activate();
			void Deactivate();



		};

	} // namespace hardware

} // namespace crowos

#endif
