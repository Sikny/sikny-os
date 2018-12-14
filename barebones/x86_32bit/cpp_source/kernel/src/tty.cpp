#include "tty.h"

void terminal_init(void){
  // positionning on top left of terminal;
  terminal_row = 0;
  terminal_column = 0;
  // write in terminal in light gray foreground, black background
  terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminal_buffer = (uint16_t*) 0xB8000;  // VGA text mode buffer
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}

void terminal_putentryat(const char c, uint8_t color, size_t col, size_t row){
	const size_t index = row * VGA_WIDTH + col;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_scroll(void){
	for(size_t i = 1; i < VGA_HEIGHT; i++){	//rows
		for(size_t j = 0; j < VGA_WIDTH; j++){	//cols
			terminal_buffer[i*VGA_WIDTH+j] = terminal_buffer[i*VGA_WIDTH+(j+VGA_WIDTH)]; // 1 line above
		}
	}
	terminal_row--;	// to stay between bounds
}

void terminal_putchar(const char c){
	if(c == '\n'){
		terminal_row++;
		terminal_column = 0;
		if (terminal_row == VGA_HEIGHT)
			terminal_scroll();
	}
	else{
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT)
				terminal_scroll();
		}
	}
}

void terminal_write(const char* data, size_t size){
	for(size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestr(const char* data){
	terminal_write(data, strlen(data));
}
