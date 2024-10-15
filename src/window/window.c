#include "termmanip.h"
#include <stdlib.h>
#include <stdlib.h>
#include "return.h"
#include <string.h>

Tm_window* tm_window(Tm_terminal* terminal, char* name, int x, int y, int columns, int rows, Tm_window* parent, enum Tm_child_type child_type) {
	Tm_window* win = malloc(sizeof(Tm_window));

	if(win == NULL) {
		tm_set_return(terminal, TM_OUT_OF_MEM);
		return NULL;
	}

	win->terminal = terminal;

	if (terminal != NULL) {
	Tm_window** windows_temp = NULL;
	windows_temp = realloc(terminal->windows, sizeof(Tm_window*) * (terminal->window_amount + 1));

		if (windows_temp == NULL) {
		tm_set_return(terminal, TM_OUT_OF_MEM);
		return (struct Tm_window*)TM_ERROR;
	}

	terminal->windows = windows_temp;

	terminal->window_amount++;

	terminal->windows[terminal->window_amount - 1] = win;
	}

	win->buffer = NULL;

	win->children = NULL;

	win->selected_child_window = NULL;
	win->selected_child_window_id = 0;

	win->children_amount = 0;

	win->parent = NULL;

	win->child_type = TM_CHILD_NONE;

	win->name = malloc(strlen(name) + 1);

	if (win->name == NULL) {
		tm_set_return(terminal, TM_OUT_OF_MEM);
		return (struct Tm_window*)TM_ERROR;
	}

	strcpy(win->name, name);
	win->name[strlen(name)] = '\0';
	win->name_length = strlen(name) + 1;

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

	if(parent != NULL) {
		tm_win_parent(parent, win, child_type);
	}

	win->physical_window = malloc(sizeof(Tm_window));

	if (win->physical_window == NULL) {
		tm_set_return(terminal, TM_OUT_OF_MEM);
		return (struct Tm_window*)TM_ERROR;
	}

	memcpy(win->physical_window, win, sizeof(Tm_window));

	win->physical_window->physical_window = NULL;

	win->physical_window->buffer = malloc(sizeof(Tm_char) * win->buffer_columns * win->buffer_rows);

	if (win->physical_window->buffer == NULL) {
		tm_set_return(terminal, TM_OUT_OF_MEM);
		return (struct Tm_window*)TM_ERROR;
	}

	memcpy(win->physical_window->buffer, win->buffer, sizeof(Tm_char) * win->buffer_columns * win->buffer_rows);

	return win;
}

int tm_win_free(Tm_window* win) {
	if(win == NULL) {
		return 0;
	}

	// Remove win from its parents child window array if it is a child

	int win_parent_child_id = 0;

	if(win->child_type != TM_CHILD_NONE) {
		for(int i = 0; i < win->parent->children_amount; i++) {
			if(win->parent->children[i] == win) {
				i = win_parent_child_id;
				break;
			}
		}

		for(int i = win_parent_child_id; i < win->parent->children_amount - 1; i++) {
			win->parent->children[i] = win->parent->children[i + 1];
		}

		win->parent->children = realloc(win->parent->children, sizeof(Tm_window*) * win->parent->children_amount - 1);

		if(win->parent->children == NULL) {
			tm_set_return(win->terminal, TM_OUT_OF_MEM);
			return TM_ERROR;
		}
		
		win->parent->children_amount--;
	}

	int total_child_window_amount = win->children_amount;

	for(int i = 0; i < total_child_window_amount; i++) {
		tm_win_free(win->children[0]);
	}

	free(win->physical_buffer);
	win->physical_buffer = NULL;
	free(win->children);
	win->children = NULL;
	free(win->buffer);
	win->buffer = NULL;
	free(win->name);
	win->name = NULL;
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
