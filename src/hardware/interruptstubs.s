.set IRQ_BASE, 0x20

.section .text

.extern _ZN6crowos8hardware16InterruptManager15handleInterruptEhj

.global _ZN6crowos8hardware16InterruptManager22IgnoreInterruptRequestEv

.macro HandleException num
.global _ZN6crowos8hardware16InterruptManager19HandleException\num\()Ev
_ZN6crowos8hardware16InterruptManager19HandleException\num\()Ev:
	movb $\num, (interruptNumber)
	jmp int_bottom
.endm

.macro HandleInterruptRequest num
.global _ZN6crowos8hardware16InterruptManager26HandleInterruptRequest\num\()Ev
_ZN6crowos8hardware16InterruptManager26HandleInterruptRequest\num\()Ev:
	movb $\num + IRQ_BASE, (interruptNumber)
	pushl $0
	jmp int_bottom
.endm

HandleException 0x00
HandleException 0x01
HandleException 0x02
HandleException 0x03
HandleException 0x04
HandleException 0x05
HandleException 0x06
HandleException 0x07
HandleException 0x08
HandleException 0x09
HandleException 0x0A
HandleException 0x0B
HandleException 0x0C
HandleException 0x0D
HandleException 0x0E
HandleException 0x0F
HandleException 0x10
HandleException 0x11
HandleException 0x12
HandleException 0x13

HandleInterruptRequest 0x00			# Timer
HandleInterruptRequest 0x01			# Keyboard
HandleInterruptRequest 0x02
HandleInterruptRequest 0x03
HandleInterruptRequest 0x04
HandleInterruptRequest 0x05
HandleInterruptRequest 0x06
HandleInterruptRequest 0x07
HandleInterruptRequest 0x08
HandleInterruptRequest 0x09
HandleInterruptRequest 0x0A
HandleInterruptRequest 0x0B
HandleInterruptRequest 0x0C			# Mouse
HandleInterruptRequest 0x0D
HandleInterruptRequest 0x0E
HandleInterruptRequest 0x0F

HandleInterruptRequest 0x80

int_bottom:  
    pushl %ebp
    pushl %edi
    pushl %esi
    pushl %edx
    pushl %ecx
    pushl %ebx
    pushl %eax
    pushl %esp
    push (interruptNumber)
    call _ZN6crowos8hardware16InterruptManager15handleInterruptEhj
    mov %eax, %esp # switch the stack
    popl %eax
    popl %ebx
    popl %ecx
    popl %edx
    popl %esi
    popl %edi
    popl %ebp
	add $4, %esp

_ZN6crowos8hardware16InterruptManager22IgnoreInterruptRequestEv:
	iret

.data
	interruptNumber: .byte 0
