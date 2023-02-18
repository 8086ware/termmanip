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


