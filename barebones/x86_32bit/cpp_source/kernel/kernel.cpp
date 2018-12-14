#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "tty.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

// Kernel entry
extern "C" void kernel_main(void){
  terminal_init();
	for(vga_color ind = VGA_COLOR_BLUE; ind <= VGA_COLOR_WHITE; ind = (vga_color)((int) ind + 1)){
		terminal_color = vga_entry_color(ind, VGA_COLOR_BLACK);
		terminal_writestr("ok");
	}
	for(vga_color ind = VGA_COLOR_BLUE; ind <= VGA_COLOR_WHITE; ind = (vga_color) ((int) ind + 1)){
		terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, ind);
		terminal_writestr("ok");
	}
}
