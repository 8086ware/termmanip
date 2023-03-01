#include "termmanip.h"

int tm_win_modify(Tm_window* win, int x, int y, int columns, int rows) {
	int scr_x, scr_y;

	tm_get_scrsize(&scr_x, &scr_y);

	if(x < 0 || y < 0 || x > scr_x || y > scr_y) {
		tm_error_number = TM_INVALID_DIMENSIONS;
		return TM_ERROR;
	}
	
	win->position_x = x;
	win->position_y = y;

	win->columns = columns;
	win->rows = rows;

	return 0;
}


