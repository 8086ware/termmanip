#include "termmanip.h"
#include <stdio.h>

void tm_win_raw(Tm_window* win, int state) {
	if(state <= 0) {
		win->flags &= ~TM_FLAG_RAW;
	}

	else if(state > 0) {	
		win->flags |= TM_FLAG_RAW;
	}
}
