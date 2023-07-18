#include "screen.h"
#include "termmanip.h"
#include <stdlib.h>
#include "error.h"

int screen_resize() {
	int scr_x, scr_y;
	tm_get_scrsize(&scr_x, &scr_y);
	tm_win_modify(default_win, 0, 0, scr_x, scr_y);
	tm_win_clear(default_win);
	
	int columns, rows;
	tm_get_scrsize(&columns, &rows);

	screen->buffer = realloc(screen->buffer, sizeof(Tm_char) * columns * rows);

	if(screen->buffer == NULL) {
		tm_set_error(TM_OUT_OF_MEM);
		return TM_ERROR;
	}

	for(int i = 0; i < columns * rows; i++) {
		screen->buffer[i].disp = ' ';
		screen->buffer[i].attrib = 0;
	}

	tm_screen_update();
	
	return 0;
}
