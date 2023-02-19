#include "termmanip.h"
#include "append_win.h"
#include <stdio.h>
#include <stddef.h>
#include <wchar.h>

int tm_win_cursor(Tm_window* win, int x, int y) {
	if(x < 0 || y < 0 || x > win->columns || y > win->rows) {
		return TM_INVALID_CURSOR;
	}

	win->cursor_x = x;
	win->cursor_y = y;
	
	char buffer[32];

	if(win->parent != NULL) {
		x += win->parent->position_x;
		y += win->parent->position_y;
	}

	sprintf(buffer, "\x1b[%d;%dH", y + win->position_y + 1, x + win->position_x + 1);
	
	append_win(win, buffer);

	return 0;
}