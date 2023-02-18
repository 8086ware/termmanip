#include "termmanip.h"

Tm_window* tm_window(int x, int y, int columns, int rows) {
	Tm_window* win = malloc(sizeof(Tm_window));

	if(win == NULL) {
		exit_log("tm_window", "malloc", 1);
	}

	win->cursor_x = 0;
	win->cursor_y = 0;

	win->position_x = x;
	win->position_y = y;

	win->parent = NULL;
	win->children = NULL;

	win->children_amount = 0;

	win->contents = NULL;
	win->content_len = 0;

	return win;
}

