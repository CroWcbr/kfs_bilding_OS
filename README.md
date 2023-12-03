# My own Operating System

## kfs-1 - Grub, boot and screen (finished)
- make a kernel, bootable with GRUB, who can write characters on screen
#### Bonus
- Add scroll and cursor support to your I/O interface.
- Add colors support to your I/O interface.
- Add helpers like printf / printk in order to print information / debug easily.
- Handle keyboard entries and print them.
- Handle different screens, and keyboard shortcuts to switch easily between then.

## kfs-2 - GDT & Stack (finished)
- create a Global Descriptor Table and set GDT at address 0x00000800
#### Bonus
- simple Shell (reboot, halt, stack, shutdown)
```
stupid realization.... I add class Shell in future....
```

## kfs-3 - Memory
- in plans

## kfs-4 - Interrupts
- in plans

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
