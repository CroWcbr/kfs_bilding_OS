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
            uint32 eax;
            uint32 ebx;
            uint32 ecx;
            uint32 edx;

            uint32 esi;
            uint32 edi;
            uint32 ebp;

            uint32 error;

            uint32 eip;
            uint32 cs;
            uint32 eflags;
            uint32 esp;
            uint32 ss;
        } __attribute__((packed)); 

        class SyscallHandler : public hardware::InterruptHandler
        {
        public:
            SyscallHandler(hardware::InterruptManager* interruptManager, uint8 InterruptNumber);
            ~SyscallHandler();
            
            virtual uint32 HandleInterrupt(uint32 esp);
        };

    } // namespace hardware

} // namespace crowos

#endif
