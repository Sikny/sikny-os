#ifndef TTY_H
#define TTY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "string.h"
#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint16_t* terminal_buffer;
uint8_t terminal_color;

void terminal_init(void);
void terminal_putentryat(const char c, uint8_t color, size_t col, size_t row);
void terminal_putchar(const char c);
void terminal_write(const char* data, size_t size);
void terminal_scroll(void);
void terminal_writestr(const char* data);

#endif
