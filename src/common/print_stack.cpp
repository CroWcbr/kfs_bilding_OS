#include <common/stdio.h>
#include <common/types.h>

namespace crowos
{
	namespace common
	{

		void print_stack(void* ptr)
		{
			if (!ptr)
			{
				printf("stack ptr == NULL\n");
				return;
			}

			uint8* test = (uint8*)ptr;
			int value_in_row = 16;
			int numBytes = 10 * value_in_row;

			printf("0x%p : ", test);
			for (int i = 0; i < numBytes; ++i)
			{
				if (test[i] > 15)
					printf("%x ", test[i]);
				else
					printf("0%x ", test[i]);

				if ((i != 0 && (i + 1) % value_in_row == 0) || i == numBytes - 1)
					for (int ii = i - 16; ii <  i; ++ii)
						printf("%c", ((char)test[ii] <= 32) ? '.' : (char)test[ii]);		

				if (i != 0 && (i + 1) % value_in_row == 0 && i != numBytes - 1)
					printf("\n0x%p : ", &test[i + 1]);
			}
			printf("\n");
		}
	}
}
