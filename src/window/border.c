#include "termmanip.h"

void tm_win_border(Tm_window* win) {
	int temp_x = tm_win_get_cursor_x(win);
	int temp_y = tm_win_get_cursor_y(win);

	for(int i = 0; i < tm_win_get_buffer_columns(win); i++) {
		tm_win_cursor(win, i, 0);
		tm_win_putch(win, '\x71', tm_win_get_attrib(win) | TM_ATTRIB_ALTERNATE);
	}

	for(int i = 0; i < tm_win_get_buffer_columns(win); i++) {
		tm_win_cursor(win, i, tm_win_get_buffer_rows(win) - 1);
		tm_win_putch(win, '\x71', tm_win_get_attrib(win) | TM_ATTRIB_ALTERNATE);
	}

	for(int i = 0; i < tm_win_get_buffer_rows(win); i++) {
		tm_win_cursor(win, 0, i);
		tm_win_putch(win, '\x78', tm_win_get_attrib(win) | TM_ATTRIB_ALTERNATE);
	}

	for(int i = 0; i < tm_win_get_buffer_rows(win); i++) {
		tm_win_cursor(win, tm_win_get_buffer_columns(win) - 1, i);
		tm_win_putch(win, '\x78', tm_win_get_attrib(win) | TM_ATTRIB_ALTERNATE);
	}

	tm_win_cursor(win, 0, 0);
	tm_win_putch(win, '\x6c', TM_ATTRIB_ALTERNATE | tm_win_get_attrib(win));
	tm_win_cursor(win, tm_win_get_buffer_columns(win) - 1, 0);
	tm_win_putch(win, '\x6b', TM_ATTRIB_ALTERNATE | tm_win_get_attrib(win));
	tm_win_cursor(win, 0, tm_win_get_buffer_rows(win) - 1);
	tm_win_putch(win, '\x6d', TM_ATTRIB_ALTERNATE | tm_win_get_attrib(win));
	tm_win_cursor(win, tm_win_get_buffer_columns(win) - 1, tm_win_get_buffer_rows(win) - 1);
	tm_win_putch(win, '\x6a', TM_ATTRIB_ALTERNATE | tm_win_get_attrib(win));
	
	tm_win_cursor(win, temp_x, temp_y);
}
