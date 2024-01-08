#include "termmanip.h"

void tm_win_clear(Tm_window* win) {
	tm_win_cursor(win, 0, 0);
	
	for(int y = 0; y < tm_win_get_buffer_rows(win); y++) {
		for(int x = 0; x < tm_win_get_buffer_columns(win); x++) {
			tm_win_putch(win, tm_win_get_background(win).disp, tm_win_get_background(win).attrib);
		}
	}

	tm_win_attrib(win, TM_ATTRIB_ALL, 0);
	tm_win_attrib(win, tm_win_get_background(win).disp, tm_win_get_background(win).attrib);
	
	tm_win_cursor(win, 0, 0);
}
