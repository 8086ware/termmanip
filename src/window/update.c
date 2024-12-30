#include "termmanip.h"
#include "terminal.h"

int tm_win_update(Tm_window* win) {
	tm_win_mark_for_update(win);

	return tm_terminal_update(win->terminal);
}

void tm_win_mark_for_update(Tm_window* win) {
	win->update = 1;

	terminal_win_order_topmost(win);

	for (int i = 0; i < win->children_amount; i++) {
		tm_win_mark_for_update(win->children[i]);
	}

	win->terminal->last_updated_window = win;
}
