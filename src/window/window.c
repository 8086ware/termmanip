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
	
	win->buffer = NULL;
	
	tm_win_modify(win, x, y, columns, rows);
	
	win->cursor_x = 0;
	win->cursor_y = 0;
	
	win->parent = NULL;
	win->children = NULL;

	win->children_amount = 0;
	win->child_type = TM_CHILD_NONE;

	win->flags = 0;
	win->attrib = TM_ATTRIB_FG_DEFAULT | TM_ATTRIB_BG_DEFAULT;

	tm_win_background(win, ' ', TM_ATTRIB_FG_DEFAULT | TM_ATTRIB_BG_DEFAULT);
	tm_win_echo(win, 1);
	tm_win_raw(win, 1);
	tm_win_cursor_visible(win, 1);
	return win;
}

void tm_win_free(Tm_window* win) {
	if(win == NULL) {
		return;
	}

	if(win->child_type != TM_CHILD_NONE) {
		for(int i = 0; i < win->parent->children_amount; i++) {
			if(win->parent->children[i] == win) {
				Tm_window* temp = win->parent->children[win->parent->children_amount - 1];

				win->parent->children[win->parent->children_amount - 1] = win;
				win->parent->children[i] = temp;

				win->parent->children = realloc(win->parent->children, sizeof(Tm_window) * (win->parent->children_amount - 1));

				win->parent->children_amount--;

				if(win->parent->children == NULL && win->parent->children_amount != 0) {
					exit_log("tm_win_free", "realloc", 1);
				}		
			}
		}
	}

	for(int i = 0; i < win->children_amount; i++) {
		tm_win_free(win->children[i]);
	}

	free(win->children);
	win->children = NULL;
	free(win->buffer);
	win->buffer = NULL;
	free(win);
}
