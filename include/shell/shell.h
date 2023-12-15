#ifndef __CROW__SHELL_H
#define __CROW__SHELL_H

#include <vga/screen.h>
#include <common/types.h>
#include <vga/screen.h>

namespace crowos
{
	namespace shell
	{

		class Shell
        {
        private:

        public:
            static void exec_cmd(char *command, crowos::vga::Screen *my_screen);
        };

	}
}

#endif
