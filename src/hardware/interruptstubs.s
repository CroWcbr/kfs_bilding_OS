.set IRQ_BASE, 0x20

.section .text

.extern _ZN6crowos8hardware16InterruptManager15handleInterruptEhj

.global _ZN6crowos8hardware16InterruptManager22IgnoreInterruptRequestEv

.macro HandleException num
.global _ZN6crowos8hardware16InterruptManager16HandleException\num\()Ev
_ZN6crowos8hardware16InterruptManager16HandleException\num\()Ev:
	movb $\num, (interruptNumber)
	jmp int_bottom
.endm

.macro HandleInterruptRequest num
.global _ZN6crowos8hardware16InterruptManager26HandleInterruptRequest\num\()Ev
_ZN6crowos8hardware16InterruptManager26HandleInterruptRequest\num\()Ev:
	movb $\num + IRQ_BASE, (interruptNumber)
	jmp int_bottom
.endm

HandleInterruptRequest 0x00			# Timer
HandleInterruptRequest 0x01			# Keyboard
HandleInterruptRequest 0x0C			# Mouse

int_bottom:
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs

	pushl %esp
	push (interruptNumber)
	call _ZN6crowos8hardware16InterruptManager15handleInterruptEhj
	movl %eax, %esp

	popl %gs
	popl %fs
	popl %es
	popl %ds
	popa

_ZN6crowos8hardware16InterruptManager22IgnoreInterruptRequestEv:

	iret 

.data
	interruptNumber: .byte 0
