#include "termmanip.h" 
#include <string.h>
#include "error.h"

int tm_win_putch(Tm_window* win, char ch, uint32_t attrib) {
	int ret = 0;

	if(ch == '\x1b') {
		return 0;
	}

	else if(ch == '\r') {
		ret = tm_win_cursor(win, 0, tm_win_get_cursor_y(win));
	}

	else if(ch == '\n') {
		ret = tm_win_cursor(win, 0, tm_win_get_cursor_y(win) + 1);
	}

	else if(ch == '\b' || ch == '\177') {
		ret = tm_win_cursor(win, tm_win_get_cursor_x(win) - 1, tm_win_get_cursor_y(win));
	}

	else if(ch == '\t') {
		ret = tm_win_cursor(win, tm_win_get_cursor_x(win) + 4, tm_win_get_cursor_y(win));
	}

	else {
		ret = tm_win_cursor(win, tm_win_get_cursor_x(win) + 1, tm_win_get_cursor_y(win));

		win->buffer[tm_win_get_cursor_y(win) * win->buffer_columns + tm_win_get_cursor_x(win) - 1].attrib = attrib;
		win->buffer[tm_win_get_cursor_y(win) * win->buffer_columns + tm_win_get_cursor_x(win) - 1].disp = ch;
	}

	return ret;
}

int tm_win_puts(Tm_window* win, char* str, uint32_t attrib) {
	int ret = 0;

	for(; *str != '\0'; str++) {
		if((ret = tm_win_putch(win, *str, attrib)) == TM_ERROR) {
			return ret;
		}
	}

	return 0;
}
