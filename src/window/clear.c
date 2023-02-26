#include "termmanip.h"
#include "append_win.h"

void tm_win_clear(Tm_window* win) {
//	tm_win_memclear(win);

	for(int y = 0; y < win->rows; y++) {
		for(int x = 0; x < win->columns; x++) {
			tm_win_cursor(win, x, y);
			append_win_ch(win, ' ');
		}
	}

	tm_win_cursor(win, 0, 0);
}
