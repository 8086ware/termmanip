#include "termmanip.h"

int tm_win_modify(Tm_window* win, int x, int y, int columns, int rows) {
	int scr_x, scr_y;

	tm_get_scrsize(&scr_x, &scr_y);

	if(columns > scr_x) {
		columns = scr_x;
	}

	if(rows > scr_y) {
		rows = scr_y;
	}

	if(x < 0) {
		x = 0;
	}

	if(y < 0) {
		y = 0;
	}

	win->position_x = x;
	win->position_y = y;

	win->columns = columns;
	win->rows = rows;

	return 0;
}


