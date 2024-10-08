#include "termmanip.h"
#include <stdlib.h>
#include "return.h"
#include "terminal.h"

int tm_win_modify(Tm_window* win, int x, int y, int columns, int rows, _Bool resize_buffer) {
	int scr_x, scr_y;

	tm_get_termsize(&scr_x, &scr_y);

	if(rows <= 0) {
		rows = 1;
	}

	if(columns <= 0) {
		columns = 1;
	}

	if(x < 0) {
		x = 0;
	}

	if(y < 0) {
		y = 0;
	}

	if(x + columns > scr_x) {
		columns -= scr_x - (x + columns);
	}

	if(y + rows > scr_y) {
		rows -= scr_y - (y + rows);
	}

	// Save flags and turn them all off when modifying the window, for example TM_FLAG_BORDER which needs to be removed when modifying a window

	int flags = win->flags;

	tm_win_flags(win, TM_ATTRIB_ALL, 0);

	update_terminal_flags(win);

	win->position_x = x;
	win->position_y = y;

	win->columns = columns;
	win->rows = rows;

	win->physical_buffer = realloc(win->physical_buffer, sizeof(Tm_char) * win->columns * win->rows);

	if (win->physical_buffer == NULL) {
		tm_set_return(win->terminal, TM_OUT_OF_MEM);
		return TM_ERROR;
	}

	if(resize_buffer) {
		win->buffer_columns = columns;
		win->buffer_rows = rows;

		win->buffer = realloc(win->buffer, sizeof(Tm_char) * win->columns * win->rows);

		if(win->buffer == NULL) {
			tm_set_return(win->terminal, TM_OUT_OF_MEM);
			return TM_ERROR;
		}

		tm_win_clear(win);

		win->buffer_position_x = 0;
		win->buffer_position_y = 0;
	}

	else {
		if(win->buffer_position_x + columns > win->buffer_columns) {
			tm_win_scroll(win, (win->buffer_position_x + columns) - win->buffer_columns, TM_SCROLL_RIGHT);
		}

		if(win->buffer_position_y + rows > win->buffer_rows) {
			tm_win_scroll(win, (win->buffer_position_y + rows) - win->buffer_rows, TM_SCROLL_DOWN);
		}
	}

	// Turn all the flags previously had on and update the terminal flags
	tm_win_flags(win, flags, 1);

	update_terminal_flags(win);

	return 0;
}

