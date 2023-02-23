#include "termmanip.h"

int tm_win_fill(Tm_window* win, int from_x, int from_y, int to_x, int to_y, char ch) {
	int ret = 0;

	for(int y = from_y; y < to_y; y++) {
		for(int x = from_x; x < to_x; x++) {
			if((ret = tm_win_cursor(win, x, y))) {
				return ret;
			}

			if((ret = tm_win_print_ch(win, ch))) {
				return ret;
			}
		}
	}

	return 0;
}
