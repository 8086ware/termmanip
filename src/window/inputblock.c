#include "termmanip.h"
#include <stdio.h>

void tm_win_inputblock(Tm_window* win, int state) {
	if(state <= 0) {
		win->flags &= ~TM_FLAG_INPUTBLOCK;
	}

	else if(state > 0) {	
		win->flags |= TM_FLAG_INPUTBLOCK;
	}
}
