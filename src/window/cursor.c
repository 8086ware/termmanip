#include "termmanip.h"
#include <stdio.h>
#include <string.h>

int tm_win_cursor(Tm_window* win, int x, int y) {
	int i = y * win->columns + x;

	if(i > win->columns * win->rows || i < 0) {
		tm_error_number = TM_INVALID_CURSOR;
		return TM_ERROR;
	}

	win->cursor_x = i % win->columns;
	win->cursor_y = i / win->columns;	

	return 0;
}

int tm_win_cursor_visible(Tm_window* win, int state) {
	if(state <= 0) {
		return append_win(win, TM_ESC_DISABLE_CURSOR);
	}
	
	else if(state > 0) {
		return append_win(win, TM_ESC_ENABLE_CURSOR);
	}

	return 0;
}

