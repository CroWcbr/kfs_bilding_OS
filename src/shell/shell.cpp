#include <shell/shell.h>
#include <hardware/port.h>
#include <common/types.h>
#include <common/stdio.h>
#include <common/utils.h>
#include <vga/screen.h>

namespace crowos::shell
{

namespace
{
    void cmd_stack()
    {
        int x;
        __asm__ ("mov %%esp, %0" : "=r"(x) ::);
        print_stack((uint8*)x);
    }

    void cmd_reboot()
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

    void cmd_shutdown()
    {
        hardware::Port16bit dataport(0x604);
        dataport.Write(0x2000); // for QEMU
        // dataport.Write(0x3400); // for VM 
    }

    void cmd_halt()
    {
        __asm__ ("hlt");
        __asm__ ("int $0x3");
    }

    void cmd_clear()
    {
        vga::Screen::getInstance().clear();
    }

    void cmd_help()
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

    struct Command
    {
        const char* name;
        void (*handler)();
    };

    static Command commands[] = {
    {"stack",    cmd_stack},
    {"reboot",   cmd_reboot},
    {"shutdown", cmd_shutdown},
    {"halt",     cmd_halt},
    {"clear",    cmd_clear},
    {"help",     cmd_help}
    };
}

void Shell::exec_cmd(char *command)
{
    if (!*command)
        ;
   
    for (auto &cmd : commands)
    {
        if (!common::strcmp(command, cmd.name))
        {
            cmd.handler();
            return;
        }
    }
}

} // namespace crowos::shell
