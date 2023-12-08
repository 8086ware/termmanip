#ifndef SCREEN_H
#define SCREEN_H

#include "termmanip.h"
#include <stdint.h>

int terminal_init();
int terminal_free();

void terminal_cursor(int x, int y);

void terminal_attrib(uint32_t attrib);

void terminal_write(int x, int y, char ch, uint32_t attrib);
void terminal_make_output();
int terminal_append_output(char* fmt, ...);

int terminal_resize();

#endif
