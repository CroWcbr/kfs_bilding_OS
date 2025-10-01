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
			uint16	portnumber;

			Port(uint16 portnumber);
			~Port();
		};

		class Port8bit : public Port
		{
		public:
			Port8bit(uint16 portnumber);
			~Port8bit();

			virtual void		Write(uint8 data);
			virtual uint8		Read();
		};

		class Port8bitSlow: public Port8bit
		{
		public:
			Port8bitSlow(uint16 portnumber);
			~Port8bitSlow();

			virtual void		Write(uint8 data);
		};

		class Port16bit : public Port
		{
		public:
			Port16bit(uint16 portnumber);
			~Port16bit();

			virtual void		Write(uint16 data);
			virtual uint16	Read();
		};

		class Port32bit : public Port
		{
		public:
			Port32bit(uint16 portnumber);
			~Port32bit();

			virtual void	Write(uint32 data);
			virtual uint32	Read();
		};

	} // namespace hardware

} // namespace crowos

#endif
