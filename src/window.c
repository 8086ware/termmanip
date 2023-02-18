#include "termmanip.h"

Tm_window* tm_window(int x, int y, int columns, int rows) {
	int ret = 0;
	
	Tm_window* win = malloc(sizeof(Tm_window));

	if(win == NULL) {
		exit_log("tm_window", "malloc", 1);
	}
	
	if(ret = tm_win_modify(win, x, y, columns, rows)) {
		return (Tm_window*)ret;
	}

	win->parent = NULL;
	win->children = NULL;

	win->children_amount = 0;

	win->contents = NULL;
	win->content_len = 0;

	return win;
}

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


