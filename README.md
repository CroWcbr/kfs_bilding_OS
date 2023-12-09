# My own Operating System

## TODO kfs4
- Create an Interrupts Descriptor Table, fill it and register it (finished)
- A signal-callback system on your Kernel API (draft)
- An interface to schedule signals
- An interface to clean registers before a panic / halt
- An interface to save the stack before a panic
- Syscalls
- multi keyboard (qwerty, azerty)
- get_line function

## kfs-1 - Grub, boot and screen (finished)
- make a kernel, bootable with GRUB, who can write characters on screen
- code the interface between your kernel and the screen
- display "42" on the screen
#### Bonus
- Add scroll and cursor support to your I/O interface.
- Add colors support to your I/O interface.
- Add helpers like printf / printk in order to print information / debug easily.
- Handle keyboard entries and print them.
- Handle different screens, and keyboard shortcuts to switch easily between then.

## kfs-2 - GDT & Stack (finished)
- create a Global Descriptor Table and set GDT at address 0x00000800
#### Bonus
- simple Shell (reboot, halt, stack, shutdown, clear)
```
stupid realization.... I add class Shell in future....
```

## kfs-3 - Memory
- reading theory

## kfs-4 - Interrupts (in progress)
- Create an Interrupts Descriptor Table, fill it and register it
- A signal-callback system on your Kernel API
- An interface to schedule signals
- An interface to clean registers before a panic / halt
- An interface to save the stack before a panic
#### Bonus
- Syscalls
- multi keyboard (qwerty, azerty)
- get_line function

## Sources
- materials
```
https://wiki.osdev.org/Main_Page
https://www.gnu.org/software/grub/manual/multiboot/multiboot.html
https://littleosbook.github.io/
```
- video tutorials with explanations
```
https://www.youtube.com/@writeyourownoperatingsystem
https://www.youtube.com/@nanobyte-dev
```

## Resourse
- QEMU with GDB : qemu-system-i386 -kernel mykernel.bin -monitor stdio
- QEMU with debugger: qemu-system-i386 -kernel mykernel.bin -d cpu,memory,...
