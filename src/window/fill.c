#include "termmanip.h"

int tm_win_fill(Tm_window* win, int from_x, int from_y, int to_x, int to_y, char ch, uint32_t attrib) {
	int ret = 0;

	int cur_x = win->cursor_x, cur_y = win->cursor_y;

	for(int y = from_y; y < to_y; y++) {
		for(int x = from_x; x < to_x; x++) {
			if((ret = tm_win_putch(win, x, y, ch, attrib)) == TM_ERROR) {
				return ret;
			}
		}
	}

	if((ret = tm_win_cursor(win, cur_x, cur_y)) == TM_ERROR) {
		return ret;
	}

	return 0;
}
