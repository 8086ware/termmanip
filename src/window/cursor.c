#include "termmanip.h"
#include "append_win.h"
#include <stdio.h>
#include <string.h>

int tm_win_cursor(Tm_window* win, int x, int y) {
	if(x >= win->columns) {
		x = 0;
		y++;
	}

	else if(x < 0) {
		x = win->columns - 1;
		y--;
	}
	
	if(y >= win->rows || y < 0) {
		tm_error_number = TM_INVALID_CURSOR;
		return TM_ERROR;
	}

	win->cursor_x = x;
	win->cursor_y = y;
	
	if(win->parent != NULL) {
		x += win->parent->position_x;
		y += win->parent->position_y;
	}

	return append_win(win, "\x1b[%d;%dH", y + win->position_y + 1, x + win->position_x + 1);
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

