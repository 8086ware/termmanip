#include "termmanip.h"
#include <stdio.h>
#include <string.h>
#include "return.h"

int tm_win_cursor(Tm_window* win, int x, int y) {
	if(win->flags & TM_FLAG_SCROLL) {
		if(y > tm_win_get_rows(win) - 1 + tm_win_get_buffer_pos_y(win)) {
			tm_win_scroll(win, y - (tm_win_get_rows(win) - 1 + tm_win_get_buffer_pos_y(win)), TM_SCROLL_DOWN);
		}

		else if(y < win->buffer_position_y) {		
			tm_win_scroll(win, tm_win_get_buffer_pos_y(win)- y, TM_SCROLL_UP);
		}

		if(x > tm_win_get_columns(win) - 1 + tm_win_get_buffer_pos_x(win)) {
			tm_win_scroll(win, x - (tm_win_get_columns(win) - 1 + tm_win_get_buffer_pos_x(win)), TM_SCROLL_RIGHT);
		}

		else if(x < win->buffer_position_x) {		
			tm_win_scroll(win, tm_win_get_buffer_pos_x(win)- x, TM_SCROLL_LEFT);
		}
	}

	else if(y < 0 || y > tm_win_get_buffer_rows(win) - 1 || x < 0 || x > tm_win_get_buffer_columns(win) - 1) {
		tm_set_return(TM_INVALID_CURSOR);
		return TM_ERROR;
	}

	win->cursor_x = x;
	win->cursor_y = y;

	return 0;
}

