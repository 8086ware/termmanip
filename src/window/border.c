#include "termmanip.h"

int tm_win_border(Tm_window* win) {
	int temp_x = win->cursor_x;
	int temp_y = win->cursor_y;

	for(int y = 0; y < win->buffer_rows; y++) {
		for(int x = 0; x < win->buffer_columns; x++) {
			tm_win_cursor(win, x, y);
			if(x == 0 || x == win->buffer_columns - 1) {
				tm_win_putch(win, '\x78', TM_ATTRIB_ALTERNATE | win->attrib);
			}

			if(y == 0 || y == win->buffer_rows - 1) {
				tm_win_putch(win, '\x71', TM_ATTRIB_ALTERNATE | win->attrib);
			}
		}
	}
	
	tm_win_cursor(win, 0, 0);
	tm_win_putch(win, '\x6c', TM_ATTRIB_ALTERNATE | win->attrib);
	tm_win_cursor(win, win->buffer_columns - 1, 0);
	tm_win_putch(win, '\x6b', TM_ATTRIB_ALTERNATE | win->attrib);
	tm_win_cursor(win, 0, win->buffer_rows - 1);
	tm_win_putch(win, '\x6d', TM_ATTRIB_ALTERNATE | win->attrib);
	tm_win_cursor(win, win->buffer_columns - 1, win->buffer_rows - 1);
	tm_win_putch(win, '\x6a', TM_ATTRIB_ALTERNATE | win->attrib);
	
	tm_win_cursor(win, temp_x, temp_y);
	return 0;
}
