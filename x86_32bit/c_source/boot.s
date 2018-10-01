/* multiboot header constants */
/*note :  multiboot header is a data structure in the kernel image that
 provides information to a Multiboot-compliant boot loader (GRUB for
 instance) about how and where to load the image, and which multiboot
 features the image expects.*/
.set ALIGN,    1<<0 /*align loaded modules on page boundaries*/
.set MEMINFO,  1<<1 /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */

/* Multiboot header */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* on x86, stack is 16-byte aligned */
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

/* Entry point, bootloader will jump to this point once kernel has been
 loaded. Function no needs return : bootloader is gone */
.section .text
.global _start
.type _start, @function
_start:
      mov $stack_top, %esp
/* now esp  register(=current stack pointer) points to the top of the stack
 (it grows downwards on x86 systems)*/

/* There can be initialized crucial processor states */

/* now calling high level kernel (C) */
      call kernel_main

/* And Infinite loop, if the system has nothing more to do */
      cli /* disables interrupts */
lb:   hlt /* waits for interrupts, which are disabled, so just
            locks computer */
      jmp lb

.size _start, . - _start /* for debugging */
