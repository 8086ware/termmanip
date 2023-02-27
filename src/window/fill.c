#include "termmanip.h"
#include "append_win.h"

int tm_win_fill(Tm_window* win, int from_x, int from_y, int to_x, int to_y, char ch, int attrib) {
	int ret = 0;

	int cur_x = win->cursor_x, cur_y = win->cursor_y;

	tm_win_attrib(win, attrib);

	for(int y = from_y; y < to_y; y++) {
		for(int x = from_x; x < to_x; x++) {
			if((ret = tm_win_cursor(win, x, y))) {
				return ret;
			}

			append_win(win, "%c", ch);
		}
	}

	tm_win_attrib(win, TM_ATTRIB_RESET);
	tm_win_cursor(win, cur_x, cur_y);

	return 0;
}
