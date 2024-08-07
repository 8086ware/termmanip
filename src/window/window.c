#include "termmanip.h"
#include <stdlib.h>
#include <stdlib.h>
#include "return.h"

Tm_window* tm_window(Tm_terminal* terminal, int x, int y, int columns, int rows) {
	Tm_window* win = malloc(sizeof(Tm_window));

	if(win == NULL) {
		tm_set_return(terminal, TM_OUT_OF_MEM);
		return NULL;
	}

	win->terminal = terminal;

	win->buffer = NULL;
	
	win->parent = NULL;
	win->children = NULL;

	win->children_amount = 0;
	win->child_type = TM_CHILD_NONE;

	win->flags = 0;

	win->background_tm_char.attrib = 0;
	win->background_tm_char.disp = ' ';

	win->position_x = x;
	win->position_y = y;

	win->columns = columns;
	win->rows = rows;

	win->buffer_position_x = 0;
	win->buffer_position_y = 0;

	win->buffer_columns = win->columns;
	win->buffer_rows = win->rows;

	win->buffer = malloc(sizeof(Tm_char) * win->buffer_columns * win->buffer_rows);
	win->physical_buffer = malloc(sizeof(Tm_char) * win->columns * win->rows);

	if(win->buffer == NULL) {
		tm_set_return(terminal, TM_OUT_OF_MEM);
		return (struct Tm_window*)TM_ERROR;
	}

	tm_win_attrib(win, TM_ATTRIB_ALL, 0);
	tm_win_background(win, ' ', 0);

	for(int i = 0; i < win->columns * win->rows; i++) {
		win->physical_buffer[i] = tm_win_get_background(win);
	}

	tm_win_clear(win);
	tm_win_flags(win, TM_FLAG_ECHO | TM_FLAG_CURSOR_VISIBLE, 1);

	tm_win_cursor(win, 0, 0);
	
	tm_win_input_timeout(win, -1);

	return win;
}

int tm_win_free(Tm_window* win) {
	if(win == NULL) {
		return 0;
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
					tm_set_return(win->terminal, TM_OUT_OF_MEM);
					return TM_ERROR;
				}	
			}
		}
	}

	for(int i = 0; i < win->children_amount; i++) {
		tm_win_free(win->children[i]);
	}

	free(win->physical_buffer);
	win->physical_buffer = NULL;
	free(win->children);
	win->children = NULL;
	free(win->buffer);
	win->buffer = NULL;
	free(win);

	return 0;
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

Tm_char tm_win_get_background(Tm_window* win) {
	return win->background_tm_char;
}

enum Tm_attrib tm_win_get_attrib(Tm_window* win) {
	return win->attrib;
}

enum Tm_window_flags tm_win_get_flags(Tm_window* win) {
	return win->flags;
}
