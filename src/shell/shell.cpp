#include <shell/shell.h>
#include <hardware/port.h>
#include <common/types.h>
#include <common/stdio.h>

namespace crowos::shell
{

void Shell::exec_cmd(char *command, vga::Screen *my_screen)
{
    if (!*command)
        ;
    else if (command[0] == 's' && \
        command[1] == 't' && \
        command[2] == 'a' && \
        command[3] == 'c' && \
        command[4] == 'k' && \
        command[5] == 0)
    {
        int x;
        __asm__ ("mov %%esp, %0" : "=r"(x) ::); // stack pointer
        print_stack((uint8*)x);
    }
    else if (command[0] == 'r' && \
            command[1] == 'e' && \
            command[2] == 'b' && \
            command[3] == 'o' && \
            command[4] == 'o' && \
            command[5] == 't' && \
            command[6] == 0)
    {
        uint8 good = 0x02;

        hardware::Port16bit dataport(0x64);
        // Poll bit 1 of the Status Register ("Input buffer empty/full") until it becomes clear.
        while (good & 0x02)
            good = dataport.Read();

        // Set the reset line bit to 0
        dataport.Write(0xFE);
        __asm__ ("hlt");
    }
    else if (command[0] == 's' && \
            command[1] == 'h' && \
            command[2] == 'u' && \
            command[3] == 't' && \
            command[4] == 'd' && \
            command[5] == 'o' && \
            command[6] == 'w' && \
            command[7] == 'n' && \
            command[8] == 0)
    {
        hardware::Port16bit dataport(0x604);
        dataport.Write(0x2000); // for QEMU
        // dataport.Write(0x3400); // for VM
    }
    else if (command[0] == 'h' && \
            command[1] == 'a' && \
            command[2] == 'l' && \
            command[3] == 't' && \
            command[4] == 0)
    {
        __asm__ ("hlt");
        __asm__ ("int $0x3");
    }
    else if (command[0] == 'c' && \
            command[1] == 'l' && \
            command[2] == 'e' && \
            command[3] == 'a' && \
            command[4] == 'r' && \
            command[5] == 0)
    {
        my_screen->clear();
    }
    else if (command[0] == 'h' && \
            command[1] == 'e' && \
            command[2] == 'l' && \
            command[3] == 'p' && \
            command[4] == 0)
    {
			const char *help_info = R"(CROW Kernel:
    F1-F3      - change screen
    F4         - change layout
kernel command :
    stack      - print stack
    halt       - stop all
    shutdown   - turn off kernel
    help       - print info
    clear      - clear screen
    reboot     - reboot kernel
)";
        printf("%s", help_info);
    }
	else
		printf("It is not command!\n");
}

} // namespace crowos::shell
