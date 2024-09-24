#include "termmanip.h"
#include <stdlib.h>
#include "return.h"

int tm_win_scroll(Tm_window* win, int amount, enum Tm_scroll direction) {
	_Bool new_buffer = 0; // This is turned on when the window buffer needs to be extended

	int og_cols = win->buffer_columns, og_rows = win->buffer_rows;

	switch(direction) {
		case TM_SCROLL_DOWN:
			if(win->buffer_position_y + win->rows + amount > win->buffer_rows) {
				win->buffer_rows = win->rows + win->buffer_position_y + amount;

				new_buffer = 1;
			}
			win->buffer_position_y += amount;
			break;

		case TM_SCROLL_UP: 
			if(win->buffer_position_y - amount < 0) {
				amount = win->buffer_position_y;
			}

			win->buffer_position_y -= amount;
			break;

		case TM_SCROLL_RIGHT:
			if(win->buffer_position_x + win->columns + amount > win->buffer_columns) {
				win->buffer_columns = win->columns + win->buffer_position_x + amount;
				new_buffer = 1;
			}

			win->buffer_position_x += amount;
			break;

		case TM_SCROLL_LEFT: 
			if(win->buffer_position_x - amount < 0) {
				amount = win->buffer_position_x;
			}

			win->buffer_position_x -= amount;
			break;
	}

	if(new_buffer) {
		Tm_char* temp = malloc(sizeof(Tm_char) * og_cols * og_rows);

		for(int i = 0; i < og_cols * og_rows; i++) {
			temp[i] = win->buffer[i];
		}

		win->buffer = realloc(win->buffer, sizeof(Tm_char) * win->buffer_columns * win->buffer_rows);
		
		if(win->buffer == NULL) {
			tm_set_return(win->terminal, TM_OUT_OF_MEM);
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

	return 0;
}
