#include "termmanip.h"
#include <unistd.h>
#include <stdio.h>
#include "append_output.h"
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

void terminal_move_cursor(int x, int y) {
	if(y != screen->cursor_y) {
		append_output("\x1b[%d;%dH", y + 1, x + 1);
		return;
	}

	if(x - screen->cursor_x == 1) {
		return;
	}

	if(x - screen->cursor_x < 8 && x - screen->cursor_x > 1) {
		for(int i = 1; i < x - screen->cursor_x; i++) {
			append_output(" ");
		}
	}

	else {
		append_output("\x1b[%d;%dH", y + 1, x + 1);
	}

	append_output(win, "\x1b[%d;%dH", win->cursor_y + win->position_y + 1 + parent_y, win->cursor_x + win->position_x + 1 + parent_x);

	if(found) {
#ifdef _WIN32
		DWORD bytes_written = 0;
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), win->output, win->output_len, &bytes_written, NULL);
#else
		write(fileno(stdout), win->output, win->output_len);
#endif
	}

	free(win->output);
	win->output = NULL;
	win->output_len = 0;

	for(int i = 0; i < win->columns * win->rows; i++) {
		win->physical_buffer[i].disp = win->buffer[i].disp;
		win->physical_buffer[i].attrib = win->buffer[i].attrib;
	}

	for(int i = 0; i < win->children_amount; i++) {
		tm_win_update(win->children[i]);
	}

}
