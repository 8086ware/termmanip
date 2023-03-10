#include "termmanip.h"
#include "append_win.h"
#include <stdio.h>
#include <string.h>

int tm_win_cursor_internal(Tm_window* win, int x, int y) {
	int i =	y * win->columns + x;

	if(y >= win->rows || y < 0) {
		tm_error_number = TM_INVALID_CURSOR;
		return TM_ERROR;
	}

	x = i % win->columns;
	y = i / win->columns;

	win->cursor_x = x;
	win->cursor_y = y;
	
	return 0;
}

int tm_win_cursor(Tm_window* win, int x, int y) {
	int ret = 0;

	if((ret = tm_win_cursor_internal(win, x, y)) == TM_ERROR) {
		return ret;
	}

	int parent_x = 0;
	int parent_y = 0;

	if(win->parent != NULL) {
		parent_x = win->parent->position_x;
		parent_y = win->parent->position_y;
	}

	return append_win(win, "\x1b[%d;%dH", parent_y + win->cursor_y + win->position_y + 1, parent_x + win->cursor_x + win->position_x + 1);
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

