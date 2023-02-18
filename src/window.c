#include "termmanip.h"

Tm_window* tm_window(int x, int y, int columns, int rows) {
	Tm_window* win = malloc(sizeof(Tm_window));

	if(win == NULL) {
		exit_log("tm_window", "malloc", 1);
	}
	
	tm_win_modify(win, x, y, columns, rows);

	win->parent = NULL;
	win->children = NULL;

	win->children_amount = 0;

	win->contents = NULL;
	win->content_len = 0;

	return win;
}

int tm_win_modify(Tm_window* win, int x, int y, int columns, int rows) {
	win->position_x = x;
	win->position_y = y;

	win->columns = columns;
	win->rows = rows;
}


