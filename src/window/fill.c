#include "termmanip.h"

void tm_win_fill(Tm_window* win, int from_x, int from_y, int to_x, int to_y, char ch, uint32_t attrib) {
	int cur_x = tm_win_get_cursor_x(win), cur_y = tm_win_get_cursor_y(win);

	for(int y = from_y; y < to_y; y++) {
		for(int x = from_x; x < to_x; x++) {
			tm_win_cursor(win, x, y);
			tm_win_putch(win, ch, attrib);
		}
	}

	tm_win_cursor(win, cur_x, cur_y);
}
