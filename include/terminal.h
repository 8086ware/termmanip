#ifndef TERMINAL_H 
#define TERMINAL_H 

#include "termmanip.h"
#include <stdint.h>

void terminal_write(Tm_terminal* terminal, int x, int y, char ch, uint32_t attrib);
void terminal_make_output(Tm_terminal* terminal);
int terminal_append_output(Tm_terminal* terminal, char* fmt, ...);

int terminal_resize(Tm_terminal* terminal);

#endif
