#include "termmanip.h"
#include "append_win.h"
#include <string.h>

int check_cursor_over_rows(Tm_window* win) {
	if(win->cursor_y >= win->rows) {
		return TM_INVALID_CURSOR;
	}

	return 0;
}

int check_wrap_line(Tm_window* win) {
	int ret = 0;

	if(win->cursor_x >= win->columns) {
		if((ret = tm_win_cursor(win, 0, win->cursor_y + 1))) {
			return ret;
		}
	}

	return 0;
}

int tm_win_print_str(Tm_window* win, char* text) {
	int ret = 0;

	if((ret = check_cursor_over_rows(win) == TM_INVALID_CURSOR)) {
		return ret;
	}

	for(; *text!= '\0'; text++) {
		if((ret = tm_win_print_ch(win, *text))) {
			return ret;
		}
	}

	return 0;
}

int tm_win_print_ch(Tm_window* win, char ch) {
	int ret = 0;

	if((ret = check_cursor_over_rows(win) == TM_INVALID_CURSOR)) {
		return ret;
	}

	append_win(win, &ch);

	win->cursor_x++;

	if((ret = check_wrap_line(win))) {
			return ret;
	}

	return 0;
}
