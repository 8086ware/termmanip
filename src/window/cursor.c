#include "termmanip.h"
#include "append_win.h"
#include <stdio.h>
#include <string.h>

int tm_win_cursor(Tm_window* win, int x, int y) {
	if(x < 0) {
		x = 0;
	}

	if(y < 0) {
		y = 0;
	}

	if(x >= win->columns) {
		x = win->columns - 1;	
	}

	if(y >= win->rows) {
		y = win->rows - 1;
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

