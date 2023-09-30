#include "terminal.h"
#include "termmanip.h"
#include <stdlib.h>
#include "error.h"	
#include <stdio.h>
#include <memory.h>

int terminal_resize() {
	int scr_x, scr_y;
	tm_get_scrsize(&scr_x, &scr_y);
	tm_win_modify(default_win, 0, 0, scr_x, scr_y);

	Tm_char* temp = malloc(sizeof(Tm_char) * terminal->columns * terminal->rows);

	memcpy(temp, terminal->buffer, sizeof(Tm_char) * terminal->columns * terminal->rows);

	terminal->buffer = realloc(terminal->buffer, sizeof(Tm_char) * scr_x * scr_y);

	int og_cols = terminal->columns, og_rows = terminal->rows;

	terminal->columns = scr_x;
	terminal->rows = scr_y;

	for(int i = 0; i < terminal->columns * terminal->rows; i++) {
		Tm_char ch;
		ch.attrib = 0;
		ch.disp = ' ';

		terminal_buffer_write(i % terminal->columns, i / terminal->columns, ch);
		terminal_output_write(i % terminal->columns, i / terminal->columns, ch.disp, ch.attrib);
	}

	for(int y = 0; y < og_rows; y++) {
		for(int x = 0; x < og_cols; x++) {
			if(x < terminal->columns && y < terminal->rows) {
				terminal_buffer_write(x, y, temp[y * og_cols + x]);
				terminal_output_write(x, y, temp[y * og_cols + x].disp, temp[y * og_cols + x].attrib);
			}
		}
	}

	free(temp);
	
	tm_terminal_update();

	return 0;
}
