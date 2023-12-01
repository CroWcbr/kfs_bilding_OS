#include <common/types.h>
#include <devicemanager/screenmanager.h>

using namespace crowos::devicemanager;

namespace crowos
{
	namespace common
	{

		void print_shell_promt()
		{
			ScreenManager& my_screen = ScreenManager::getInstance();

			my_screen.print_shell_promt();
		}

	}
}
