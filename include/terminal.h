#ifndef SCREEN_H
#define SCREEN_H

#include "termmanip.h"
#include <stdint.h>

int terminal_init();
void terminal_free();

void terminal_cursor(int x, int y);

void terminal_attrib(uint32_t attrib);

void terminal_output_write(int x, int y, char ch, uint32_t attrib);
int terminal_append_output(char* fmt, ...);

void terminal_buffer_write(int x, int y, Tm_char ch);

int terminal_resize();

#endif
