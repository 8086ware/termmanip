#include "termmanip.h"

void tm_win_flags(Tm_window* win, uint16_t flags, int state) {
	if(state <= 0) {
		win->flags &= ~flags;
	}

	else if(state > 0) {	
		win->flags |= flags;
	}
}
