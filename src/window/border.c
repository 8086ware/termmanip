#include "termmanip.h"

int tm_win_border(Tm_window* win) {
	int ret = 0;

	int columns, rows;

	int cur_x = win->cursor_x, cur_y = win->cursor_y;

	tm_get_winsize(win, &columns, &rows);

	for(int y = 0; y < rows; y++) {
		for(int x = 0; x < columns; x++) {
			if(x == 0 || x == columns - 1) {
				tm_win_putch(win, x, y, '\x78', TM_ATTRIB_ALTERNATE | win->attrib);
			}

			if(y == 0 || y == rows - 1) {
				tm_win_putch(win, x, y, '\x71', TM_ATTRIB_ALTERNATE | win->attrib);
			}
		}
	}
	
	tm_win_putch(win, 0, 0, '\x6c', TM_ATTRIB_ALTERNATE | win->attrib);
	tm_win_putch(win, columns - 1, 0, '\x6b', TM_ATTRIB_ALTERNATE | win->attrib);
	tm_win_putch(win, 0, rows - 1, '\x6d', TM_ATTRIB_ALTERNATE | win->attrib);
	tm_win_putch(win, columns - 1, rows - 1, '\x6a', TM_ATTRIB_ALTERNATE | win->attrib);

	return 0;
}
