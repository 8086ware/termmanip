#include "termmanip.h"
#include "append_win.h"
#include <string.h>

void handle_escape_codes(Tm_window* win, char escape) {
	switch(escape) {
	case '\n': {
		tm_win_cursor(win, 0, win->cursor_y + 1);
		break;
	}
	}

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

	for(; *text!= '\0'; text++) {
		if((ret = tm_win_print_ch(win, *text))) {
			return ret;
		}
	}

	return 0;
}

int tm_win_print_ch(Tm_window* win, char ch) {
	int ret = 0;

	if((ret = check_wrap_line(win))) {
			return ret;
	}
	
	if(ch == '\n' || ch == '\b') {
		handle_escape_codes(win, ch);
		return 0;
	}

	append_win_ch(win, ch);

	win->cursor_x++;

	return 0;
}
