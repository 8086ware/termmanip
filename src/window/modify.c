#include "termmanip.h"
#include <stdlib.h>
#include "return.h"

int tm_win_modify(Tm_window* win, int x, int y, int columns, int rows, _Bool resize_buffer) {
	int scr_x, scr_y;

	tm_get_scrsize(&scr_x, &scr_y);

	if(rows <= 0) {
		rows = 1;
	}

	if(columns <= 0) {
		columns = 1;
	}

	if(x < 0) {
		x = 0;
	}

	if(y < 0) {
		y = 0;
	}

	if(x + columns > scr_x) {
		columns -= scr_x - (x + columns);
	}

	if(y + rows > scr_y) {
		rows -= scr_y - (y + rows);
	}

	win->position_x = x;
	win->position_y = y;

	win->columns = columns;
	win->rows = rows;

	win->physical_buffer = realloc(win->physical_buffer, sizeof(Tm_char) * win->columns * win->rows);

	if(win->buffer_columns < columns || win->buffer_rows < rows) {
		int og_cols = win->buffer_columns, og_rows = win->buffer_rows;

		win->buffer_columns = columns;
		win->buffer_rows = rows;

		Tm_char* temp = malloc(sizeof(Tm_char) * og_cols * og_rows);

		for(int i = 0; i < og_cols * og_rows; i++) {
			temp[i] = win->buffer[i];
		}

		win->buffer = realloc(win->buffer, sizeof(Tm_char) * win->buffer_columns * win->buffer_rows);

		if(win->buffer == NULL) {
			tm_set_return(TM_OUT_OF_MEM);
			return TM_ERROR;
		}

		for(int i = 0; i < win->buffer_columns * win->buffer_rows; i++) { 
			win->buffer[i] = tm_win_get_background(win);
		}
		
		for(int y = 0; y < og_rows; y++) {
			for(int x = 0; x < og_cols; x++) {
				if(x < win->buffer_columns && y < win->buffer_rows) { 
					win->buffer[y * win->buffer_columns + x] = temp[y * og_cols + x];
				}
			}
		}

		free(temp);
	}

	else if(resize_buffer) {
		win->buffer_columns = columns;
		win->buffer_rows = rows;

		win->buffer = realloc(win->buffer, sizeof(Tm_char) * win->columns * win->rows);

		if(win->buffer == NULL) {
			tm_set_return(TM_OUT_OF_MEM);
			return TM_ERROR;
		}

		tm_win_clear(win);

		win->buffer_position_x = 0;
		win->buffer_position_y = 0;
	}

	return 0;
}

