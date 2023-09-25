#include "screen.h"
#include "termmanip.h"

void screen_buffer_write(int x, int y, Tm_char ch) {
	int position = y * screen->columns + x;

	y = position / screen->columns;
	x = position % screen->columns;

	if(ch.disp != screen->buffer[position].disp || ch.attrib != screen->buffer[position].attrib) {
		screen_output_write(x, y, ch.disp, ch.attrib);
	}

	screen->buffer[position] = ch;
}
