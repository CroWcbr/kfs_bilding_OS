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
			crowos::common::uint8_t interruptNumber;
			InterruptManager* interruptManager;

			InterruptHandler(crowos::common::uint8_t interruptNumber, InterruptManager* interruptManager);
			InterruptHandler();
		public:
			virtual crowos::common::uint32_t HandleInterrupt(crowos::common::uint32_t esp);
		};

		class InterruptManager
		{
		friend class InterruptHandler;
		protected:

			static InterruptManager* ActivateInterruptManager;
			InterruptHandler* handlers[256];

			struct GateDescriptor
			{
				crowos::common::uint16_t	handlerAddresLowBits;
				crowos::common::uint16_t	gdt_codeSegmentSelector;
				crowos::common::uint8_t		reserved;
				crowos::common::uint8_t		access;
				crowos::common::uint16_t	handlerAddresHighBits;
			} __attribute__((packed));

			static GateDescriptor interruptDescriptorTable[256];

			struct InterruptDescriptionTablePointer
			{
				crowos::common::uint16_t	size;
				crowos::common::uint32_t	base;
			} __attribute__((packed));

			static void SetIterruptDescriptorTable(
				crowos::common::uint8_t interruptNumber,
				crowos::common::uint16_t gdt_codeSegmentSelectorOffset,
				void (*handler)(),
				crowos::common::uint8_t DescriptorPrivilegeLevel,
				crowos::common::uint8_t DescriptorType);

			Port8bitSlow	picMasterCommand;
			Port8bitSlow	picMasterData;
			Port8bitSlow	picSlaveCommand;
			Port8bitSlow	picSlaveData;

			static crowos::common::uint32_t	handleInterrupt(crowos::common::uint8_t interruptNumber, crowos::common::uint32_t esp);
			crowos::common::uint32_t		DoHandleInterrupt(crowos::common::uint8_t interruptNumber, crowos::common::uint32_t esp);
			void							isr_handler(crowos::common::uint8_t interruptNumber);
			void							irq_handler(crowos::common::uint8_t interruptNumber);
			void							clean_all_registers();

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
			InterruptManager(crowos::GlobalDescriptorTable* gdt);
			~InterruptManager();

			void Activate();
			void Deactivate();



		};
	}
}

#endif
