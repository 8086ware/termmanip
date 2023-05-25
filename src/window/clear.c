#include "termmanip.h"

int tm_win_clear(Tm_window* win) {
	int ret = 0;

	tm_win_cursor(win, 0, 0);
	
	for(int y = 0; y < win->buffer_rows; y++) {
		for(int x = 0; x < win->buffer_columns; x++) {
			tm_win_putch(win, win->background_tm_char.disp, win->background_tm_char.attrib);
		}
	}

	tm_win_attrib(win, TM_ATTRIB_ALL, 0);
	tm_win_attrib(win, win->background_tm_char.disp, win->background_tm_char.attrib);
	
	tm_win_cursor(win, 0, 0);

	for(int i = 0; i < win->children_amount; i++) {
		tm_win_clear(win->children[i]);
	}

	return 0;
}
