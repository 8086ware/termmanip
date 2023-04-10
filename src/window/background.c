#include "termmanip.h"
#include <stdlib.h>
#include <string.h>
#include "exit_log.h"

int tm_win_background(Tm_window* win, uint32_t attrib) {
	int ret = 0;

	int temp_cursor_x = win->cursor_x, temp_cursor_y = win->cursor_y;

	for(int y = 0; y < win->rows; y++) {
		for(int x = 0; x < win->columns; x++) {
			tm_win_putch(win, x, y, win->buffer[y * win->columns + x].disp, attrib);
		}
	}

	if((ret = tm_win_cursor(win, temp_cursor_x, temp_cursor_y)) == TM_ERROR) {
		return ret;	
	}

	tm_win_attrib(win, TM_ATTRIB_ALL, 0);
	tm_win_attrib(win, attrib, 1);

	return 0;
}
