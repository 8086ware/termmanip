#include "termmanip.h"
#include "terminal.h"

void terminal_write(Tm_terminal* terminal, int x, int y, char ch, uint32_t attrib) {
	int position = y * terminal->columns + x;

	if(position > terminal->columns * terminal->rows - 1 || position < 0) {
		return;
	}

	y = position / terminal->columns;
	x = position % terminal->columns;

	if(ch == terminal->buffer[position].disp && attrib == terminal->buffer[position].attrib) {
		return;
	}

	terminal->buffer[position].disp = ch;
	terminal->buffer[position].attrib = attrib;
}

