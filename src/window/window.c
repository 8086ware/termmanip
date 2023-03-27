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

	win->columns = columns;
	win->rows = rows;

	win->position_x = x;
	win->position_y = y;
	
	win->cursor_x = 0;
	win->cursor_y = 0;
	
	win->parent = NULL;
	win->children = NULL;

	win->children_amount = 0;

	win->flags = 0;

	win->cursor_visible = 1;
	win->cursor_moved = 0;

	win->attrib = TM_ATTRIB_RESET;

	win->buffer = malloc(sizeof(Tm_char) * win->columns * win->rows);
	win->physical_buffer = malloc(sizeof(Tm_char) * win->columns * win->rows);

	if(win->buffer == NULL || win->physical_buffer == NULL) {
		exit_log("tm_window", "malloc", 2);
	}
	
	for(int i = 0; i < win->columns * win->rows; i++) {
		win->buffer[i].disp = '\0';
		win->buffer[i].attrib = TM_ATTRIB_RESET;
		win->physical_buffer[i].disp = '\0';
		win->physical_buffer[i].attrib = TM_ATTRIB_RESET;
	}

	tm_win_echo(win, 1);
	tm_win_raw(win, 1);

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
	win->children = NULL;
	free(win->buffer);
	win->buffer = NULL;
	free(win->physical_buffer);
	win->physical_buffer = NULL;
	free(win);
	win = NULL;
}
