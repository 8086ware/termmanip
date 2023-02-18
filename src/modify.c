#include "termmanip.h"

int tm_win_modify(Tm_window* win, int x, int y, int columns, int rows) {
	if(win == NULL) {
		return TM_WIN_NULL;
	}

	int scr_x, scr_y;

	tm_get_scrsize(&scr_x, &scr_y);

	if(x > scr_x || y > scr_y || x < 0 || y < 0) {
		return TM_WIN_INVALID_DIMENSIONS;
	}

	win->position_x = x;
	win->position_y = y;

	win->columns = columns;
	win->rows = rows;

	return 0;
}


