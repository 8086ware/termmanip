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

	int scr_x, scr_y;
	tm_get_scrsize(&scr_x, &scr_y);

#ifdef _WIN32
	INPUT_RECORD input;
	DWORD bytes_read;
	PeekConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &input, 1, &bytes_read);

	if(bytes_read > 0) {
		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &input, 1, &bytes_read);

		if(input.EventType == WINDOW_BUFFER_SIZE_EVENT) {
			screen_resize();
		}
	}
#endif
}

