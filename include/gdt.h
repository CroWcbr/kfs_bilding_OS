#ifndef __CROWOS__GDT_H
#define __CROWOS__GDT_H

#include <common/types.h>

namespace crowos
{
	class GlobalDescriptorTable
	{
	public:
		class SegmentDescriptior
		{
		private:
			crowos::common::uint16_t	limit_lo;
			crowos::common::uint16_t	base_lo;
			crowos::common::uint8_t		base_hi;
			crowos::common::uint8_t		type;
			crowos::common::uint8_t		flags_limit_hi;
			crowos::common::uint8_t		base_vhi;
		public:
			SegmentDescriptior(crowos::common::uint32_t base, crowos::common::uint32_t limit, crowos::common::uint8_t type);

			crowos::common::uint32_t	Base();
			crowos::common::uint32_t	Limit();
		} __attribute__((packed));

		SegmentDescriptior nullSegmentSelector;
		SegmentDescriptior unusedSegmentSelector;
		SegmentDescriptior codeSegmentSelector;
		SegmentDescriptior dataSegmentSelector;

	public:
		GlobalDescriptorTable();
		~GlobalDescriptorTable();

		crowos::common::uint16_t	CodeSegmentSelector();
		crowos::common::uint16_t	DataSegmentSelector();
	};
}

#endif
