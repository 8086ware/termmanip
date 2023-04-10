#include "termmanip.h"

int tm_win_clear(Tm_window* win) {
	int ret = 0;

	if((ret = tm_win_cursor(win, 0, 0)) == TM_ERROR) {
		return ret;
	}
	
	for(int y = 0; y < win->rows; y++) {
		for(int x = 0; x < win->columns; x++) {
			tm_win_putch(win, x, y, ' ', 0);
		}
	}

	tm_win_attrib(win, TM_ATTRIB_ALL, 0);

	if((ret = tm_win_cursor(win, 0, 0)) == TM_ERROR) {
		return ret;
	}

	for(int i = 0; i < win->children_amount; i++) {
		tm_win_clear(win->children[i]);
	}

	return 0;
}
