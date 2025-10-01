#include <hardware/syscalls.h>
#include <common/stdio.h>

namespace crowos::hardware
{

SyscallHandler::SyscallHandler(InterruptManager* interruptManager, uint8 InterruptNumber)
:InterruptHandler(InterruptNumber + 0x20, interruptManager)
{
}

SyscallHandler::~SyscallHandler()
{
}

uint32 SyscallHandler::HandleInterrupt(uint32 esp)
{
    CPUState* cpu = (CPUState*)esp;
    printf("eax : %u\n", cpu->eax);
    printf("ebx : %s\n", cpu->ebx);
    printf("ecx : %u\n", cpu->ecx);
    printf("edx : %u\n", cpu->edx);
    printf("ecx : %u\n", cpu->esi);
    printf("edx : %u\n", cpu->edi);
    printf("ecx : %u\n", cpu->ebp);
    printf("edx : %u\n", cpu->eip);
    printf("edx : %u\n", cpu->cs);
    printf("edx : %u\n", cpu->eflags);
    printf("edx : %u\n", cpu->esp);
    printf("edx : %u\n", cpu->ss);
    switch(cpu->eax)
    {
        case 4:
            printf((char*)cpu->ebx);
            break;

        default:
            break;
    }

    return esp;
}

} // namespace crowos::hardware