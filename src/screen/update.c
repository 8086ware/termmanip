#include "termmanip.h"
#include "screen.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#include <io.h>
#else
#include <unistd.h>
#endif

void tm_screen_update() {
	if(screen->last_updated_x + 1 != screen->cursor_x || screen->last_updated_y != screen->cursor_y) {
		screen_append_output("\x1b[%d;%dH", screen->cursor_y + 1, screen->cursor_x + 1);
	}

	write(fileno(stdout), screen->output, screen->output_len);

	free(screen->output);
	screen->output_len = 0;
	screen->output = NULL;
}


