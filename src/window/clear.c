#include "termmanip.h"
#include "append_win.h"

int tm_win_clear(Tm_window* win) {
	int ret = 0;
	for(int y = 0; y < win->rows; y++) {
		for(int x = 0; x < win->columns; x++) {
			if((ret = tm_win_cursor(win, x, y)) == TM_ERROR) {
				return ret;
			}	

			if((ret = append_win(win, " ")) == TM_ERROR) {
				return ret;
			}	
		}
	}

	if((ret = tm_win_cursor(win, 0, 0)) == TM_ERROR) {
		return ret;
	}

	return 0;
}
