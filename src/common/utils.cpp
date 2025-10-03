#include <common/utils.h>

namespace crowos
{

	namespace common
	{

        int32 strcmp(const int8 *s1, const int8 *s2)
        {
            while (*s1 && (*s1 == *s2))
            {
                s1++;
                s2++;
            }
            return (uint8)*s1 - (uint8)*s2;
        }

        uint32 strlen(const int8* str)
        {
            uint32 len = 0;
            while (*str++)
            {
                ++len;
            }
            return len;
        }

    } // namespace common

} // namespace crowos