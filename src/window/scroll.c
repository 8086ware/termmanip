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
		for(int y = amount; y < win->rows; y++) {
			for(int x = 0; x < win->columns; x++) {
				win->buffer[(y - amount) * win->columns + x].disp = win->buffer[y * win->columns + x].disp;
				win->buffer[(y - amount) * win->columns + x].attrib = win->buffer[y * win->columns + x].attrib;
				win->buffer[y * win->columns + x].disp = ' ';
				win->buffer[y * win->columns + x].attrib = 0;
			}
		}
	}
	
	win->cursor_x = 0;
	win->cursor_y -= amount;
}
