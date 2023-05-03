#include "termmanip.h"
#include <stdlib.h>
#include "exit_log.h"

void tm_win_scroll_state(Tm_window* win, int state) {
	if(state <= 0) {
		win->flags &= ~TM_FLAG_SCROLL;
	}

	else if(state > 0) {	
		win->flags |= TM_FLAG_SCROLL;
	}
}

void tm_win_scroll(Tm_window* win, int amount, int direction) {
	if(direction == TM_SCROLL_DOWN) {
		if(win->buffer_position_y + win->rows + amount > win->buffer_rows) {
			win->buffer_rows = win->rows + win->buffer_position_y + amount;
			win->buffer = realloc(win->buffer, sizeof(Tm_char) * win->buffer_columns * win->buffer_rows);

			if(win->buffer == NULL) {
				exit_log("tm_win_scroll", "realloc", 1);
			}

			for(int y = win->buffer_rows - amount; y < win->buffer_rows; y++) {
				for(int x = 0; x < win->buffer_columns; x++) {
					win->buffer[y * win->columns + x].disp = win->background_tm_char.disp;
					win->buffer[y * win->columns + x].attrib = win->background_tm_char.attrib;
				}
			}

		}

		win->buffer_position_y += amount;
	}

	if(direction == TM_SCROLL_UP) {
		if(win->buffer_position_y - amount < 0) {
			amount = win->buffer_position_y;
		}
	

		win->buffer_position_y -= amount;
	}
}
