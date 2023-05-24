#include "screen.h"
#include "termmanip.h"

void screen_buffer_write(int x, int y, Tm_char ch) {
	int position = y * screen->columns + x;

	y = position / screen->columns;
	x = position % screen->columns;

	screen->buffer[position] = ch;
}
