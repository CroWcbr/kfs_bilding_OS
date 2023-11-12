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
/*
GDT Layout in memory:
 _______ _______ _______ _______ _______ _______ _______ _______
|  ptr  | f | l | flags |  ptr  |  ptr  |  ptr  | limit | limit |
	7       6       5       4       3       2       1       0
		^       ^---------- access rights
*/
			crowos::common::uint16_t	limit_lo;		// 0, 1
			crowos::common::uint16_t	base_lo;		// 2, 3
			crowos::common::uint8_t		base_hi;		// 4
			crowos::common::uint8_t		type;			// 5
			crowos::common::uint8_t		flags_limit_hi;	// 6
			crowos::common::uint8_t		base_vhi;		// 7
		public:
			SegmentDescriptior(crowos::common::uint32_t base, crowos::common::uint32_t limit, crowos::common::uint8_t type);

			crowos::common::uint32_t	Base();
			crowos::common::uint32_t	Limit();
		} __attribute__((packed));

		SegmentDescriptior nullSegmentSelector;		// empty
		SegmentDescriptior unusedSegmentSelector;	// unused
		SegmentDescriptior codeSegmentSelector;		// code/text segment
		SegmentDescriptior dataSegmentSelector;		// data segment

	public:
		GlobalDescriptorTable();
		~GlobalDescriptorTable();

		crowos::common::uint16_t	CodeSegmentSelector();
		crowos::common::uint16_t	DataSegmentSelector();
	};
}

#endif
