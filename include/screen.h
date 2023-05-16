#ifndef SCREEN_H
#define SCREEN_H

#include "termmanip.h"
#include <stdint.h>

void screen_init();
void screen_free();

int screen_cursor(int x, int y);

void screen_attrib(uint32_t attrib);

void screen_output_write(int x, int y, char ch, uint32_t attrib);
void screen_append_output(char* fmt, ...);

int screen_buffer_write(int x, int y, Tm_char ch);

#endif
