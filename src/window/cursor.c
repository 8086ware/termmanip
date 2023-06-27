#include "termmanip.h"
#include <stdio.h>
#include <string.h>

int tm_win_cursor(Tm_window* win, int x, int y) {
	int position = y * win->columns + x;

	x = position % win->columns;
	y = position / win->columns;

	if(win->flags & TM_FLAG_SCROLL) {
		if(y > win->rows - 1 + win->buffer_position_y) {
			tm_win_scroll(win, y - (win->rows - 1 + win->buffer_position_y), TM_SCROLL_DOWN);
		}

		else if(y < win->buffer_position_y) {		
			tm_win_scroll(win, win->buffer_position_y - y, TM_SCROLL_UP);
		}
	}

	else if(y > win->buffer_rows - 1 || x < 0) {
		tm_error_number = TM_INVALID_CURSOR;
		return TM_ERROR;
	}

	win->cursor_x = x;
	win->cursor_y = y;

	return 0;
}

