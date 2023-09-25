#include "terminal.h"
#include "termmanip.h"

void terminal_cursor(int x, int y) {
	int position = y * terminal->columns + x;

	y = position / terminal->columns;
	x = position % terminal->columns;

	terminal->cursor_x = x;
	terminal->cursor_y = y;
}
