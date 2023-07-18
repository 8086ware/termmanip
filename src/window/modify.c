#include "termmanip.h"
#include <stdlib.h>
#include "error.h"

int tm_win_modify(Tm_window* win, int x, int y, int columns, int rows) {
	int scr_x, scr_y;

	tm_get_scrsize(&scr_x, &scr_y);

	if(columns > scr_x) {
		columns = scr_x;
	}

	if(rows > scr_y) {
		rows = scr_y;
	}

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

	if(x > scr_x) {
		x = scr_x - columns;
	}
	
	if(y > scr_y) {
		y = scr_y - rows;
	}

	win->position_x = x;
	win->position_y = y;

	win->columns = columns;
	win->rows = rows;

	win->buffer_position_x = 0;
	win->buffer_position_y = 0;

	win->buffer_columns = win->columns;
	win->buffer_rows = win->rows;

	win->buffer = realloc(win->buffer, sizeof(Tm_char) * win->columns * win->rows);

	if(win->buffer == NULL) {
		tm_set_error(TM_OUT_OF_MEM);
		return TM_ERROR;
	}

	tm_win_clear(win);
	return 0;
}

