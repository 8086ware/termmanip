#include "terminal.h"
#include "termmanip.h"

void terminal_buffer_write(int x, int y, Tm_char ch) {
	int position = y * terminal->columns + x;

	if(position > terminal->columns * terminal->rows - 1 || position < 0) {
		return;
	}

	y = position / terminal->columns;
	x = position % terminal->columns;

	if(ch.disp != terminal->buffer[position].disp || ch.attrib != terminal->buffer[position].attrib) {
		terminal_output_write(x, y, ch.disp, ch.attrib);
	}

	terminal->buffer[position] = ch;
}
