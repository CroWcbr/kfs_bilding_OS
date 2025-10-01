#include <common/types.h>
#include <devicemanager/screenmanager.h>

namespace crowos::common
{
	namespace common
	{

		static uint8_t my_rand()
		{
			static unsigned int my_rand_seed = 42;
			my_rand_seed = my_rand_seed * 1103515245  + 12345;
			return my_rand_seed % 16;
		}

		void print_42()
		{
			devicemanager::ScreenManager& my_screen = devicemanager::ScreenManager::getInstance();
			const char *kfs = R"(
##         #######     ##    ## ########  ######  
##    ##  ##     ##    ##   ##  ##       ##    ## 
##    ##         ##    ##  ##   ##       ##       
##    ##   #######     #####    ######    ######  
######### ##           ##  ##   ##             ## 
      ##  ##           ##   ##  ##       ##    ## 
      ##  #########    ##    ## ##        ######  

)";
			for (int i = 0; kfs[i]; ++i)
			{
				if (kfs[i] == ' ' || kfs[i] == '\n')
					my_screen.putchar(kfs[i]);
				else
					my_screen.put_color_char(' ', 0, my_rand());
			}
		}

	} // namespace common

} // namespace crowos