#include "termmanip.h"
#include <stdio.h>
#include <string.h>

void tm_win_attrib(Tm_window* win, enum Tm_attrib attrib, int state) {
	if(state <= 0) {
		win->attrib &= ~attrib;
	}

	else if(state > 0) {	
		win->attrib |= attrib;
	}
}
