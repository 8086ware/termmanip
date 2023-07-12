#include "termmanip.h"

void tm_win_border(Tm_window* win) {
	int temp_x = win->cursor_x;
	int temp_y = win->cursor_y;

	for(int i = 0; i < tm_win_get_buffer_columns(win); i++) {
		tm_win_cursor(win, i, 0);
		tm_win_putch(win, '\x71', win->attrib | TM_ATTRIB_ALTERNATE);
	}

	for(int i = 0; i < tm_win_get_buffer_columns(win); i++) {
		tm_win_cursor(win, i, tm_win_get_buffer_rows(win) - 1);
		tm_win_putch(win, '\x71', win->attrib | TM_ATTRIB_ALTERNATE);
	}

	for(int i = 0; i < tm_win_get_buffer_rows(win); i++) {
		tm_win_cursor(win, 0, i);
		tm_win_putch(win, '\x78', win->attrib | TM_ATTRIB_ALTERNATE);
	}

	for(int i = 0; i < tm_win_get_buffer_rows(win); i++) {
		tm_win_cursor(win, tm_win_get_buffer_columns(win) - 1, i);
		tm_win_putch(win, '\x78', win->attrib | TM_ATTRIB_ALTERNATE);
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
}
