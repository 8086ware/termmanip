#include "termmanip.h"
#include <stdlib.h>
#include <string.h>
#include "exit_log.h"

int tm_win_background(Tm_window* win, char ch, uint32_t attrib) {
	int ret = 0;
	int temp_cursor_x = win->cursor_x, temp_cursor_y = win->cursor_y;

	if((ret = tm_win_cursor(win, 0, 0)) == TM_ERROR) {
		return ret;
	}
	
	for(int y = 0; y < win->rows; y++) {
		for(int x = 0; x < win->columns; x++) {
			if(win->buffer[y * win->columns + x].disp != win->background_tm_char.disp) {
				tm_win_putch(win, win->buffer[y * win->columns + x].disp, attrib | win->buffer[y * win->columns + x].attrib); 
			}

			else {
				tm_win_putch(win, ch, attrib); 
			}
		}
	}

	win->background_tm_char.attrib = attrib;
	win->background_tm_char.disp = ch;

	tm_win_attrib(win, TM_ATTRIB_ALL, 0);
	tm_win_attrib(win, win->background_tm_char.attrib, 1);

	if((ret = tm_win_cursor(win, temp_cursor_x, temp_cursor_y)) == TM_ERROR) {
		return ret;
	}

	return 0;
}
