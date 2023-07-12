#include "termmanip.h"
#include <stdlib.h>
#include "exit_log.h"
#include <stdlib.h>
#include "error.h"
Tm_window* default_win = NULL;

Tm_window* tm_window(int x, int y, int columns, int rows) {
	if(columns == 0 || rows == 0) {
		tm_set_error(TM_INVALID_WINDOW_SIZE);
		return NULL;
	}

	Tm_window* win = malloc(sizeof(Tm_window));

	if(win == NULL) {
		tm_set_error(TM_OUT_OF_MEM);
		return NULL;
	}
	
	win->buffer = NULL;
	
	win->parent = NULL;
	win->children = NULL;

	win->children_amount = 0;
	win->child_type = TM_CHILD_NONE;

	win->flags = 0;

	win->background_tm_char.attrib = 0;
	win->background_tm_char.disp = ' ';

	tm_win_attrib(win, TM_ATTRIB_ALL, 0);
	tm_win_modify(win, x, y, columns, rows);
	tm_win_background(win, ' ', 0);
	
	tm_win_flags(win, TM_FLAG_ECHO | TM_FLAG_RAW | TM_FLAG_INPUTBLOCK | TM_FLAG_CURSOR_VISIBLE, 1);

	tm_win_cursor(win, 0, 0);
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

int tm_win_get_cursor_x(Tm_window* win) {
	return win->cursor_x;
}

int tm_win_get_cursor_y(Tm_window* win) {
	return win->cursor_y;
}

int tm_win_get_columns(Tm_window* win) {
	return win->columns;
}

int tm_win_get_rows(Tm_window* win) {
	return win->rows;
}

int tm_win_get_pos_x(Tm_window* win) {
	return win->position_x;
}

int tm_win_get_pos_y(Tm_window* win) {
	return win->position_y;
}

int tm_win_get_buffer_columns(Tm_window* win) {
	return win->buffer_columns;
}

int tm_win_get_buffer_rows(Tm_window* win) {
	return win->buffer_rows;
}

int tm_win_get_buffer_pos_x(Tm_window* win) {
	return win->buffer_position_x;
}

int tm_win_get_buffer_pos_y(Tm_window* win) {
	return win->buffer_position_y;
}
