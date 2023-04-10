#include "termmanip.h"
#include <stdio.h>
#include <string.h>

void tm_win_attrib(Tm_window* win, uint32_t attrib, int state) {
	if(state <= 0) {
		win->attrib &= ~attrib;
	}

	else if(state > 0) {	
		win->attrib |= attrib;
	}
}
