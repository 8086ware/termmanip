#include "screen.h"
#include "termmanip.h"

int screen_buffer_write(int x, int y, Tm_char ch) {
	int position = y * screen->columns + x;

	y = position / screen->columns;
	x = position % screen->columns;

	if(y > screen->rows || y < 0) {
		tm_error_number = TM_SCREEN_INVALID_CURSOR;
		return TM_ERROR;
	}
	
	screen->buffer[position] = ch;
}
