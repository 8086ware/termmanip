#include "screen.h"
#include "termmanip.h"
#include "exit_log.h"

void screen_resize() {
	int columns, rows;
	tm_get_scrsize(&columns, &rows);

	screen->buffer = realloc(screen->buffer, sizeof(Tm_char) * columns * rows);

	if(screen->buffer == NULL) {
		exit_log("screen_resize", "realloc", 1);
	}

	screen->physical_buffer = realloc(screen->physical_buffer, sizeof(Tm_char) * columns * rows);

	if(screen->physical_buffer == NULL) {
		exit_log("screen_resize", "realloc", 1);
	}

	for(int i = 0; i < columns * rows; i++) {
		screen->buffer[i].disp = ' ';
		screen->buffer[i].attrib = 0;
		screen->physical_buffer[i].disp = ' ';
		screen->physical_buffer[i].attrib = 0;
	}
}
