#include "termmanip.h"
#include "append_win.h"
#include <stdio.h>
#include <string.h>

int tm_win_cursor(Tm_window* win, int x, int y) {
	if(x < 0 || y < 0 || x >= win->columns || y >= win->rows) {
		return TM_INVALID_CURSOR;
	}

	win->cursor_x = x;
	win->cursor_y = y;
	
	if(win->parent != NULL) {
		x += win->parent->position_x;
		y += win->parent->position_y;
	}

	append_win(win, "\x1b[%d;%dH", y + win->position_y + 1, x + win->position_x + 1);

	return 0;
}

void tm_win_cursor_visible(Tm_window* win, int state) {
	if(state <= 0) {
		append_win(win, TM_ESC_DISABLE_CURSOR);
	}
	
	else if(state > 0) {
		append_win(win, TM_ESC_ENABLE_CURSOR);
	}
}

