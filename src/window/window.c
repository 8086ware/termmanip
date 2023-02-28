#include "termmanip.h"
#include <stdlib.h>
#include "exit_log.h"
#include <stdlib.h>

Tm_window* default_win = NULL;

Tm_window* tm_window(int x, int y, int columns, int rows) {
	Tm_window* win = malloc(sizeof(Tm_window));

	if(win == NULL) {
		exit_log("tm_window", "malloc", 1);
	}

	int ret = 0;
	
	tm_win_modify(win, x, y, columns, rows);

	win->parent = NULL;
	win->children = NULL;

	win->children_amount = 0;

	win->contents = NULL;
	win->content_len = 0;

	tm_win_cursor(win, 0, 0);
	tm_win_attrib(win, TM_ATTRIB_RESET);

	return win;
}

void tm_win_free(Tm_window* win) {
	if(win == NULL) {
		return;
	}

	for(int i = 0; i < win->children_amount; i++) {
		tm_win_free(win->children[i]);
	}
	
	free(win->children);
	free(win->contents);
	free(win);
}
