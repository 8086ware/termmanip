#include "termmanip.h"
#include <string.h>

int tm_win_putch(Tm_window* win, int x, int y, char ch, uint32_t attrib) {
	int i = y * win->columns + x;

	if(i > (win->columns * win->rows) - 1 || i < 0) {
		tm_error_number = TM_INVALID_CURSOR;
		return TM_ERROR;
	}

	win->buffer[y * win->columns + x].attrib = attrib;
	win->buffer[y * win->columns + x].disp = ch;
	
	win->flags &= ~TM_FLAG_CURSOR_MOVED;
	return 0;
}

int tm_win_puts(Tm_window * win, int x, int y, char* str, uint32_t attrib) {
	int ret = 0;

	for(int i = 0; i < strlen(str); i++) {
		if((ret = tm_win_putch(win, x + i, y, str[i], attrib)) == TM_ERROR) {
			return ret;
		}
	}

	return 0;
}
