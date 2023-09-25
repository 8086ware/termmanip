#include "terminal.h"
#include "termmanip.h"
#include <stdlib.h>
#include "error.h"
#include <stdio.h>

int terminal_resize() {
	int scr_x, scr_y;
	tm_get_scrsize(&scr_x, &scr_y);
	tm_win_modify(default_win, 0, 0, scr_x, scr_y);

	terminal->buffer = realloc(terminal->buffer, sizeof(Tm_char) * scr_x * scr_y);

	if(terminal->buffer == NULL) {
		tm_set_error(TM_OUT_OF_MEM);
		return TM_ERROR;
	}

	terminal->columns = scr_x;
	terminal->rows = scr_y;
#ifdef _WIN32
	COORD size = {scr_x, scr_y};
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), size);
#endif

	return 0;
}
