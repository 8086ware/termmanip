#include "termmanip.h"

void tm_win_scroll_state(Tm_window* win, int state) {
	if(state <= 0) {
		win->flags &= ~TM_FLAG_SCROLL;
	}

	else if(state > 0) {	
		win->flags |= TM_FLAG_SCROLL;
	}
}
void tm_win_scroll(Tm_window* win, int amount, int direction) {
	int tempX = win->cursor_x;
	int tempY = win->cursor_y;

	if(direction == TM_SCROLL_DOWN) {
		for(int y = 0; y < win->rows; y++) {
			for(int x = 0; x < win->columns; x++) {
				tm_win_cursor(win, x, y - amount);
				tm_win_putch(win, win->buffer[y * win->columns + x].disp, win->buffer[y * win->columns + x].attrib);
				tm_win_fill(win, 0, y, win->columns, y + 1, ' ', 0);
			}
		}
	}

	tm_win_cursor(win, win->cursor_x, tempY - amount);
}
