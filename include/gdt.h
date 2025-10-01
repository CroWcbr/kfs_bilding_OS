#ifndef __CROWOS__GDT_H
#define __CROWOS__GDT_H

#include <common/types.h>

#define GDT_ADRESS 0x00000800

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
			uint16	limit_lo;		// 0, 1
			uint16	base_lo;		// 2, 3
			uint8	base_hi;		// 4
			uint8	type;			// 5
			uint8	flags_limit_hi;	// 6
			uint8	base_vhi;		// 7
		public:
			SegmentDescriptior(uint32 base, uint32 limit, uint8 type);

			uint32	Base();
			uint32	Limit();
		} __attribute__((packed));

		SegmentDescriptior nullSegmentSelector;		// empty
		SegmentDescriptior unusedSegmentSelector;	// unused
		SegmentDescriptior codeSegmentSelector;		// code/text segment
		SegmentDescriptior dataSegmentSelector;		// data segment

	public:
		GlobalDescriptorTable();
		~GlobalDescriptorTable();

		uint16	CodeSegmentSelector();
		uint16	DataSegmentSelector();
	};

} // namespace crowos

#endif
