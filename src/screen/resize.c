#include "screen.h"
#include "termmanip.h"
#include "exit_log.h"
#include <stdlib.h>

void screen_resize() {
	int scr_x, scr_y;
	tm_get_scrsize(&scr_x, &scr_y);
	tm_win_modify(default_win, 0, 0, scr_x, scr_y);
	tm_win_clear(default_win);
	
	int columns, rows;
	tm_get_scrsize(&columns, &rows);

	screen->buffer = realloc(screen->buffer, sizeof(Tm_char) * columns * rows);

	if(screen->buffer == NULL) {
		exit_log("screen_resize", "realloc", 1);
	}

	for(int i = 0; i < columns * rows; i++) {
		screen->buffer[i].disp = ' ';
		screen->buffer[i].attrib = 0;
	}

	tm_screen_update();
}
