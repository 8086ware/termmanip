#include "termmanip.h"
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#endif

void tm_win_echo(Tm_window* win, int state) {
	if(state <= 0) {
		win->flags &= ~TM_FLAG_ECHO;
	}

	else if(state > 0) {	
		win->flags |= TM_FLAG_ECHO;
	}
}
