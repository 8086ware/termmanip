#include "terminal.h"
#include "termmanip.h"
#include <stdlib.h>

int terminal_resize(Tm_terminal* terminal) {
	int scr_x, scr_y;
	tm_get_termsize(&scr_x, &scr_y);

	terminal->columns = scr_x;
	terminal->rows = scr_y;

	terminal->buffer = realloc(terminal->buffer, sizeof(Tm_char) * terminal->columns * terminal->rows);
	terminal->physical_buffer = realloc(terminal->physical_buffer, sizeof(Tm_char) * terminal->columns * terminal->rows);

	terminal_append_output(terminal, "\x1b[2J");
	
	Tm_char clear_ch;

	clear_ch.disp = ' ';
	clear_ch.attrib = 0;

	memset(terminal->physical_buffer, &clear_ch, sizeof(Tm_char) * terminal->columns * terminal->rows);

	tm_terminal_update(terminal);

	return 0;
}
