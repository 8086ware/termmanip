#include "termmanip.h"
#include <stdio.h>
#include <string.h>

void tm_win_attrib(Tm_window* win, uint32_t attrib) {
	win->attrib = attrib;
}
