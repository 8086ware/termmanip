#include "termmanip.h"
#include <stdio.h>
#include <string.h>
#include "return.h"

int tm_win_cursor(Tm_window* win, int x, int y) {
	if(win->flags & TM_FLAG_SCROLL) {
		if(win->cursor_y > tm_win_get_rows(win) - 1 + tm_win_get_buffer_pos_y(win)) {
			tm_win_scroll(win, win->cursor_y - (tm_win_get_rows(win) - 1 + tm_win_get_buffer_pos_y(win)), TM_SCROLL_DOWN);
		}

		else if(win->cursor_y < win->buffer_position_y) {		
			tm_win_scroll(win, tm_win_get_buffer_pos_y(win)- win->cursor_y, TM_SCROLL_UP);
		}

		if(win->cursor_x > tm_win_get_columns(win) - 1 + tm_win_get_buffer_pos_x(win)) {
			tm_win_scroll(win, win->cursor_x - (tm_win_get_columns(win) - 1 + tm_win_get_buffer_pos_x(win)), TM_SCROLL_RIGHT);
		}

		else if(win->cursor_x < win->buffer_position_x) {		
			tm_win_scroll(win, tm_win_get_buffer_pos_x(win)- win->cursor_x, TM_SCROLL_LEFT);
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

