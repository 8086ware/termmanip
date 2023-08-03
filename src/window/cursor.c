#include "termmanip.h"
#include <stdio.h>
#include <string.h>
#include "error.h"

int tm_win_cursor(Tm_window* win, int x, int y) {
	int position = y * tm_win_get_buffer_columns(win) + x;

	if(win->flags & TM_FLAG_SCROLL) {
		if(y > tm_win_get_rows(win) - 1 + tm_win_get_buffer_pos_y(win)) {
			tm_win_scroll(win, y - (tm_win_get_rows(win) - 1 + tm_win_get_buffer_pos_y(win)), TM_SCROLL_DOWN);
		}

		else if(y < win->buffer_position_y) {		
			tm_win_scroll(win, tm_win_get_buffer_pos_y(win)- y, TM_SCROLL_UP);
		}
	}

	else if(position < 0 || position > tm_win_get_buffer_columns(win) * tm_win_get_buffer_rows(win)) {
		tm_set_error(TM_INVALID_CURSOR);
		return TM_ERROR;
	}

	x = position % win->columns;
	y = position / win->columns;

	win->cursor_x = x;
	win->cursor_y = y;

	return 0;
}

