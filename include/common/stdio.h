#ifndef __CROWOS__STDIO_H
#define __CROWOS__STDIO_H

namespace crowos
{
	namespace common
	{

		void printf(const char *fmt, ...);
		void print_stack(void* ptr = (void*)0x800);		
		void print_shell_promt();

		void print_42();

	} // namespace common

	using common::printf;
	using common::print_stack;
	using common::print_shell_promt;

} // namespace crowos

#endif