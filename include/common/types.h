#ifndef __CROWOS__TYPES_H
#define __CROWOS__TYPES_H

namespace crowos
{
	namespace common
	{

		typedef char int8_t;
		typedef unsigned char uint8_t;

		typedef short int16_t;
		typedef unsigned short uint16_t;

		typedef int int32_t;
		typedef unsigned int uint32_t;

		typedef long long int int64_t;
		typedef unsigned long long int uint64_t;

	} // namespace common

	using int8  = common::int8_t;
	using uint8 = common::uint8_t;
	using int16 = common::int16_t;
	using uint16 = common::uint16_t;
	using int32 = common::int32_t;
	using uint32 = common::uint32_t;
	using int64 = common::int64_t;
	using uint64 = common::uint64_t;

} // namespace crowos

#endif
