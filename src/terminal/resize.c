#include "terminal.h"
#include "termmanip.h"
#include <stdlib.h>
#include "error.h"	
#include <stdio.h>
#include <memory.h>

int terminal_resize() {
	int scr_x, scr_y;
	tm_get_scrsize(&scr_x, &scr_y);

	Tm_char* temp = malloc(sizeof(Tm_char) * terminal->columns * terminal->rows);

	memcpy(temp, terminal->buffer, sizeof(Tm_char) * terminal->columns * terminal->rows);

	int og_cols = terminal->columns, og_rows = terminal->rows;

	terminal->columns = scr_x;
	terminal->rows = scr_y;

	terminal->buffer = realloc(terminal->buffer, sizeof(Tm_char) * terminal->columns * terminal->rows);

	for(int y = 0; y < terminal->rows; y++) {
		for(int x = 0; x < terminal->columns; x++) {
			Tm_char ch = {0, ' '};

			terminal->buffer[y * terminal->columns + x].disp = 0;
			terminal->buffer[y * terminal->columns + x].attrib = 0;

			terminal_write(x, y, ch.disp, ch.attrib);
		}
	}

	for(int y = 0; y < og_rows; y++) {
		for(int x = 0; x < og_cols; x++) {
			terminal_write(x, y, temp[y * og_cols + x].disp, temp[y * og_cols + x].attrib);
		}
	}

	tm_terminal_update();

	free(temp);

	return 0;
}
