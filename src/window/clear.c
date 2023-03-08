#include "termmanip.h"
#include "append_win.h"

int tm_win_clear(Tm_window* win) {
	int ret = 0;
	tm_win_cursor(win, 0, 0);

	for(int y = 0; y < win->rows; y++) {
		for(int x = 0; x < win->columns; x++) {
			tm_win_print(win, " ");
		}
	}

	if((ret = tm_win_cursor(win, 0, 0)) == TM_ERROR) {
		return ret;
	}

	return 0;
}
