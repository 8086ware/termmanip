#ifndef SCREEN_H
#define SCREEN_H

#include "termmanip.h"
#include <stdint.h>

int screen_init();
void screen_free();

void screen_cursor(int x, int y);

void screen_attrib(uint32_t attrib);

void screen_output_write(int x, int y, char ch, uint32_t attrib);
int screen_append_output(char* fmt, ...);

void screen_buffer_write(int x, int y, Tm_char ch);

void screen_resize();

#endif
