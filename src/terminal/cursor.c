#include "screen.h"
#include "termmanip.h"

void screen_cursor(int x, int y) {
	int position = y * screen->columns + x;

	y = position / screen->columns;
	x = position % screen->columns;

	screen->cursor_x = x;
	screen->cursor_y = y;
}
