#include "termmanip.h"
#include "terminal.h"

void terminal_win_order_topmost(Tm_window* win) {
	int win_id = 0;
	for (int i = 0; i < win->terminal->window_amount; i++) {
		if (win == win->terminal->windows[i]) {
			win_id = i;
		}
	}

	for (int i = win_id; i < win->terminal->window_amount - 1; i++) {
		win->terminal->windows[i] = win->terminal->windows[i + 1];
	}

	win->terminal->windows[win->terminal->window_amount - 1] = win;
}
