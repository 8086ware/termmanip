#include "termmanip.h"
#include "screen.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void tm_screen_update() {
	if(screen->last_updated_x + 1 != screen->cursor_x || screen->last_updated_y != screen->cursor_y) {
		screen_append_output("\x1b[%d;%dH", screen->cursor_y + 1, screen->cursor_x + 1);
	}

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


