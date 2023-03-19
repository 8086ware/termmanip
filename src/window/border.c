#include "termmanip.h"
#include "append_win.h"

int tm_win_border(Tm_window* win) {
	int ret = 0;

	int columns, rows;

	int cur_x = win->cursor_x, cur_y = win->cursor_y;

	tm_get_winsize(win, &columns, &rows);

	append_win(win, "\x1b(0");

	for(int y = 0; y < rows; y++) {
		for(int x = 0; x < columns; x++) {
			if(x == 0 || x == columns - 1) {
				if((ret = tm_win_cursor(win, x, y)) == TM_ERROR) {
					return ret;
				}

				if((ret = append_win(win, "\x78")) == TM_ERROR) {
					return ret;
				}
			}

			if(y == 0 || y == rows - 1) {
				if((ret = tm_win_cursor(win, x, y)) == TM_ERROR) {
					return ret;
				}

				if((ret = append_win(win, "\x71")) == TM_ERROR) {
					return ret;
				}
			}
		}
	}

	if((ret = tm_win_cursor(win, 0, 0)) == TM_ERROR) {
		return ret;
	}

	if((ret = append_win(win, "\x6C")) == TM_ERROR) {
		return ret;
	}

	if((ret = tm_win_cursor(win, columns - 1, 0)) == TM_ERROR) {
		return ret;
	}

	if((ret = append_win(win, "\x6B")) == TM_ERROR) {
		return ret;
	}
	
	if((ret = tm_win_cursor(win, 0, rows - 1)) == TM_ERROR) {
		return ret;
	}

	if((ret = append_win(win, "\x6D")) == TM_ERROR) {
		return ret;
	}
	
	if((ret = tm_win_cursor(win, columns - 1, rows - 1)) == TM_ERROR) {
		return ret;
	}

	if((ret = append_win(win, "\x6A")) == TM_ERROR) {
		return ret;
	}

	if((ret = append_win(win, "\x1b(B")) == TM_ERROR) {
		return ret;
	}

	if((ret = tm_win_cursor(win, cur_x, cur_y)) == TM_ERROR) {
		return ret;
	}

	return 0;
}
