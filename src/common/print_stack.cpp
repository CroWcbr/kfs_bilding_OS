#include <common/stdio.h>
#include <common/types.h>

using namespace crowos::common;

namespace crowos
{
	namespace common
	{

		void print_stack(void* ptr)
		{
			if (!ptr)
			{
				printf("ptr == NULL\n");
				return;
			}

			uint8_t* test = (uint8_t*)ptr;
			int numBytes = 11 * 8;

			test -= 5 * 8;
			printf("0x%p :\t", test);
			for (int i = 0; i < numBytes; ++i)
			{
				if (test[i] > 15)
					printf("0x%x\t", test[i]);
				else
					printf("0x0%x\t", test[i]);
				if (i != 0 && (i + 1) % 8 == 0 && i != numBytes - 1)
					printf("\n0x%p :\t", &test[i + 1]);
			}
			printf("\n");
		}

	}
}
