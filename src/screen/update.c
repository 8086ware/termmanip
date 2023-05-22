#include "termmanip.h"
#include "screen.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void tm_screen_update() {
	for(int i = 0; i != screen->columns * screen->rows; i++) {
		char disp = screen->buffer[i].disp;
		uint32_t attrib = screen->buffer[i].attrib;

		char physical_disp = screen->physical_buffer[i].disp;
		uint32_t physical_attrib = screen->physical_buffer[i].attrib;

		if(disp != physical_disp || attrib != physical_attrib) {

			// If the screen attribute doesn't match the attribute we want to display then output the new attribute

			screen_output_write(i % screen->columns, i / screen->columns, disp, attrib);
		}

	}
	
	screen_append_output("\x1b[%d;%dH", screen->cursor_y + 1, screen->cursor_x + 1);

#ifdef _WIN32
	DWORD bytes_written = 0;
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), screen->output, screen->output_len, &bytes_written, NULL);
#else
	write(fileno(stdout), screen->output, screen->output_len);
#endif

	free(screen->output);
	screen->output_len = 0;
	screen->output = NULL;
}


