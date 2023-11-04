#ifndef __CROWOS__PORT_H
#define __CROWOS__PORT_H

#include <common/types.h>

namespace crowos
{
	namespace hardware
	{
		class Port
		{
		protected:
			crowos::common::uint16_t	portnumber;

			Port(crowos::common::uint16_t portnumber);
			~Port();
		};

		class Port8bit : public Port
		{
		public:
			Port8bit(crowos::common::uint16_t portnumber);
			~Port8bit();

			virtual void		Write(crowos::common::uint8_t data);
			virtual crowos::common::uint8_t		Read();
		};

		class Port8bitSlow: public Port8bit
		{
		public:
			Port8bitSlow(crowos::common::uint16_t portnumber);
			~Port8bitSlow();

			virtual void		Write(crowos::common::uint8_t data);
		};

		class Port16bit : public Port
		{
		public:
			Port16bit(crowos::common::uint16_t portnumber);
			~Port16bit();

			virtual void		Write(crowos::common::uint16_t data);
			virtual crowos::common::uint16_t	Read();
		};

		class Port32bit : public Port
		{
		public:
			Port32bit(crowos::common::uint16_t portnumber);
			~Port32bit();

			virtual void		Write(crowos::common::uint32_t data);
			virtual crowos::common::uint32_t	Read();
		};
	}
}

#endif
