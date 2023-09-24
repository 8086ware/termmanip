#include "screen.h"
#include "termmanip.h"
#include <stdlib.h>
#include "error.h"
#include <stdio.h>

int screen_resize() {
	int scr_x, scr_y;
	tm_get_scrsize(&scr_x, &scr_y);
	tm_win_modify(default_win, 0, 0, scr_x, scr_y);

	screen->buffer = realloc(screen->buffer, sizeof(Tm_char) * scr_x * scr_y);

	if(screen->buffer == NULL) {
		tm_set_error(TM_OUT_OF_MEM);
		return TM_ERROR;
	}

	screen->cursor_x = 0;
	screen->cursor_y = 0;
	screen->last_updated_x = 0;
	screen->last_updated_y = 0;
	screen->flags = TM_FLAG_ECHO;

	free(screen->output);
	screen->output_len = 0;
	screen->attrib = 0;

	for(int i = 0; i < scr_x * scr_y; i++) {
		screen->buffer[i].disp = ' ';
		screen->buffer[i].attrib = 0;
	}

	write(fileno(stdout), "\x1b[2J\x1b[H", 7);
	screen->columns = scr_x;
	screen->rows = scr_y;
#ifdef _WIN32
	COORD size = {scr_x, scr_y};
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), size);
#endif

	return 0;
}
