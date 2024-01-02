#ifndef __CROWOS__SYSCALLS_H
#define __CROWOS__SYSCALLS_H

#include <common/types.h>
#include <hardware/interrupts.h>

namespace crowos
{
	namespace hardware
	{

        struct CPUState
        {
            common::uint32_t eax;
            common::uint32_t ebx;
            common::uint32_t ecx;
            common::uint32_t edx;

            common::uint32_t esi;
            common::uint32_t edi;
            common::uint32_t ebp;

            common::uint32_t error;

            common::uint32_t eip;
            common::uint32_t cs;
            common::uint32_t eflags;
            common::uint32_t esp;
            common::uint32_t ss;
        } __attribute__((packed)); 

        class SyscallHandler : public hardware::InterruptHandler
        {
        public:
            SyscallHandler(hardware::InterruptManager* interruptManager, crowos::common::uint8_t InterruptNumber);
            ~SyscallHandler();
            
            virtual crowos::common::uint32_t HandleInterrupt(crowos::common::uint32_t esp);
        };

    }
}

#endif
