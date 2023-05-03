#include "termmanip.h"
#include <stdio.h>
#include <string.h>

int tm_win_cursor(Tm_window* win, int x, int y) {
	int position = y * win->columns + x;

	y = position / win->columns;
	x = position % win->columns;

		tm_error_number = TM_INVALID_CURSOR;
		return TM_ERROR;
	}

	win->cursor_x = i % win->columns;
	win->cursor_y = i / win->columns;	

	return 0;
}

int tm_win_cursor_visible(Tm_window* win, int state) {
	if(state <= 0) {
		win->flags &= ~TM_FLAG_CURSOR_VISIBLE;
	}

	else if(state > 0) {	
		win->flags |= TM_FLAG_CURSOR_VISIBLE;
	}

	
	return 0;
}

