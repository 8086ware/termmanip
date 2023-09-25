#include "termmanip.h"
#include "terminal.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#include <io.h>
#else
#include <unistd.h>
#endif

void tm_terminal_update() {
	if(terminal->last_updated_x + 1 != terminal->cursor_x || terminal->last_updated_y != terminal->cursor_y) {
		terminal_append_output("\x1b[%d;%dH", terminal->cursor_y + 1, terminal->cursor_x + 1);
	}

	write(fileno(stdout), terminal->output, terminal->output_len);

	free(terminal->output);
	terminal->output_len = 0;
	terminal->output = NULL;

	int scr_x, scr_y;
	tm_get_scrsize(&scr_x, &scr_y);

#ifdef _WIN32
	INPUT_RECORD input;
	DWORD bytes_read;
	PeekConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &input, 1, &bytes_read);

	if(bytes_read > 0) {
		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &input, 1, &bytes_read);

		if(input.EventType == WINDOW_BUFFER_SIZE_EVENT) {
			terminal_resize();
		}
	}
#endif
}

