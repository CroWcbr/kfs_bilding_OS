#include <common/types.h>
#include <devicemanager/screenmanager.h>

namespace crowos
{
	namespace common
	{

		void print_shell_promt()
		{
			devicemanager::ScreenManager::getInstance().print_shell_promt();
		}

	} // namespace common

} // namespace crowos
