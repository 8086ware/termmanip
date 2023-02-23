#include "termmanip.h"
#include "append_win.h"

void tm_win_background(Tm_window* win, int attrib) {
	int cur_x = win->cursor_x, cur_y = win->cursor_y;

	for(int y = 0; y < win->rows; y++) {
		for(int x = 0; x < win->columns; x++) {
			tm_win_cursor(win, x, y);
			tm_win_attrib(win, attrib);
			tm_win_print_ch(win, ' ');
		}
	}

	tm_win_cursor(win, cur_x, cur_y);
}
