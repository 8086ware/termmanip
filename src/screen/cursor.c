#include "screen.h"
#include "termmanip.h"

int screen_cursor(int x, int y) {
	int position = y * screen->columns + x;

	y = position / screen->columns;
	x = position % screen->columns;

	if(y > screen->rows || y < 0) {
		tm_error_number = TM_SCREEN_INVALID_CURSOR;
		return TM_ERROR;
	}

	screen->cursor_x = x;
	screen->cursor_y = y;
}
