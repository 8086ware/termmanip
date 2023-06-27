#include "termmanip.h"

uint16_t tm_win_get_flags(Tm_window* win) {
	return win->flags;
}

void tm_win_flags(Tm_window* win, uint16_t flags, int state) {
	if(state <= 0) {
		win->flags &= ~flags;
	}

	else if(state > 0) {	
		win->flags |= flags;
	}
}
