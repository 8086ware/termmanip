#include "termmanip.h"

int tm_win_border(Tm_window* win) {
	int columns, rows;

	tm_get_winsize(win, &columns, &rows);

	for(int y = 0; y < rows; y++) {
		for(int x = 0; x < columns; x++) {
			tm_cursor(x, y);
			if(x == 0 || x == columns - 1) {
				tm_win_putch(win, '\x78', TM_ATTRIB_ALTERNATE | win->attrib);
			}

			if(y == 0 || y == rows - 1) {
				tm_win_putch(win, '\x71', TM_ATTRIB_ALTERNATE | win->attrib);
			}
		}
	}
	
	tm_win_cursor(win, 0, 0);
	tm_win_putch(win, '\x6c', TM_ATTRIB_ALTERNATE | win->attrib);
	tm_win_cursor(win, columns - 1, 0);
	tm_win_putch(win, '\x6b', TM_ATTRIB_ALTERNATE | win->attrib);
	tm_win_cursor(win, 0, rows - 1);
	tm_win_putch(win, '\x6d', TM_ATTRIB_ALTERNATE | win->attrib);
	tm_win_cursor(win, columns - 1, rows - 1);
	tm_win_putch(win, '\x6a', TM_ATTRIB_ALTERNATE | win->attrib);

	return 0;
}
