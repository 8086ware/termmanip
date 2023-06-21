#include "termmanip.h"
#include "exit_log.h"
#include "screen.h"
#include <stdlib.h>

void screen_init() {
	int scr_columns, scr_rows;
	tm_get_scrsize(&scr_columns, &scr_rows);
	screen = malloc(sizeof(Tm_screen));

	if(screen == NULL) {
		exit_log("tm_init", "malloc", 1);
	}

	screen->columns = scr_columns;
	screen->rows = scr_rows;

	screen->cursor_x = 0;
	screen->cursor_y = 0;

	screen->last_updated_x = 0;
	screen->last_updated_y = 0;

	screen->output = NULL;
	screen->output_len = 0;

	screen->attrib = 0;

	screen->flags = TM_FLAG_CURSOR_VISIBLE | TM_FLAG_INPUTBLOCK;
	
	screen->buffer = malloc(sizeof(Tm_char) * screen->columns * screen->rows);

	if(screen->buffer == NULL) {
		exit_log("tm_init", "malloc", 2);
	}	

	for(int i = 0; i < screen->columns * screen->rows; i++) {
		screen->buffer[i].disp = ' ';
		screen->buffer[i].attrib = 0;
	}
}

void screen_free() {
	free(screen->buffer);
	free(screen->output);
	free(screen);

	screen = NULL;
}
