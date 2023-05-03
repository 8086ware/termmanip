#include "termmanip.h" 
#include <string.h>

int tm_win_putch(Tm_window* win, char ch, uint32_t attrib) {
	int ret = 0;

	if(ch == '\n') {
		if((ret = tm_win_cursor(win, 0, win->cursor_y + 1)) == TM_ERROR) {
			return ret;
		}
	}

	else {
		win->buffer[win->cursor_y * win->columns + win->cursor_x].attrib = attrib;
		win->buffer[win->cursor_y * win->columns + win->cursor_x].disp = ch;

		if((ret = tm_win_cursor(win, win->cursor_x + 1, win->cursor_y)) == TM_ERROR) {
			return ret;
		}
	}

	return 0;
}

int tm_win_puts(Tm_window* win, char* str, uint32_t attrib) {
	int ret = 0;

	for(int i = 0; i < strlen(str); i++) {
		if((ret = tm_win_putch(win, str[i], attrib)) == TM_ERROR) {
			return ret;
		}
	}

	return 0;
}
