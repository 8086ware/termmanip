#include "termmanip.h"

void tm_get_winsize(Tm_window* win, int* columns, int* rows) {
	*columns = win->columns;
	*rows = win->rows;
}

void tm_get_winpos(Tm_window* win, int* position_x, int* position_y) {
	*position_x = win->position_x;
	*position_y = win->position_y;
}
