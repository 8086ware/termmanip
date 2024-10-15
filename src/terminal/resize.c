#include "terminal.h"
#include "termmanip.h"
#include "return.h"
#include <stdlib.h>

int terminal_resize(Tm_terminal* terminal) {
	int scr_x, scr_y;
	tm_get_termsize(&scr_x, &scr_y);

	terminal->columns = scr_x;
	terminal->rows = scr_y;

	terminal->buffer = realloc(terminal->buffer, sizeof(Tm_char) * terminal->columns * terminal->rows);
	terminal->physical_buffer = realloc(terminal->physical_buffer, sizeof(Tm_char) * terminal->columns * terminal->rows);

	if (terminal->buffer == NULL || terminal->physical_buffer == NULL) {
		tm_set_return(terminal, TM_OUT_OF_MEM);
		return TM_ERROR;
	}

	Tm_char clear_ch;

	clear_ch.disp = ' ';
	clear_ch.attrib = 0;

#ifdef _WIN32
	terminal->flags |= TM_FLAG_CURSOR_VISIBLE; // On windows cursor becomes visible when resizing window
#endif

	memset(terminal->physical_buffer, &clear_ch, sizeof(Tm_char) * terminal->columns * terminal->rows);
	memset(terminal->buffer, &clear_ch, sizeof(Tm_char) * terminal->columns * terminal->rows);

	return 0;
}
