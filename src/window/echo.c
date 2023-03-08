#include "termmanip.h"
#include <stdio.h>
#include <termios.h>

void tm_win_echo(Tm_window* win, int state) {
	if(state <= 0) {
		win->flags &= ~TM_FLAG_ECHO;
	}

	else if(state > 0) {	
		win->flags |= TM_FLAG_ECHO;
	}
}
