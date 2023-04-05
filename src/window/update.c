#include "termmanip.h"
#include <unistd.h>
#include <stdio.h>
#include "append_output.h"
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

// Move the actual terminal cursor to x, y from screen->cursor_x, screen->cursor_y in the best way possible
void terminal_move_cursor(int x, int y) {
	if(y != screen->cursor_y) {
		append_output("\x1b[%d;%dH", y + 1, x + 1);
		return;
	}

	// If the if new x is in front of screen->cursor_x, we don't need to move it.

	if(x - screen->cursor_x == 1) {
		return;
	}

	// If the new x is under 8 characters from the screen->cursor_x, use spaces to get there instead of escape codes
	if(x - screen->cursor_x < 8 && x - screen->cursor_x > 1) {
		for(int i = 1; i < x - screen->cursor_x; i++) {
			append_output(" ");
		}
	}

	// If the new x is the same as screen->cursor_x, just backspace to get there
	else if(x == screen->cursor_x) {
		append_output("\b");
	}

	else {
		append_output("\x1b[%d;%dH", y + 1, x + 1);
	}
}

void tm_screen_update() {
	for(int i = 0; i != screen->columns * screen->rows; i++) {
		char disp = screen->buffer[i].disp;
		uint32_t attrib = screen->buffer[i].attrib;

		char physical_disp = screen->physical_buffer[i].disp;
		uint32_t physical_attrib = screen->physical_buffer[i].attrib;

		if(disp != physical_disp || attrib != physical_attrib) {

			// If the screen attribute doesn't match the attribute we want to display then output the new attribute

			terminal_move_cursor(i % screen->columns, i / screen->columns);
			if(screen->attrib != attrib) {
				screen->attrib = attrib;

				if(attrib & TM_ATTRIB_BOLD) {
					append_output("\x1b[1m");
				}

				if(attrib & TM_ATTRIB_DIM) {
					append_output("\x1b[2m");
				}

				if(attrib & TM_ATTRIB_ITALIC) {
					append_output("\x1b[3m");
				}

				if(attrib & TM_ATTRIB_UNDERLINE) {
					append_output("\x1b[4m");
				}

				if(attrib & TM_ATTRIB_BLINKING) {
					append_output("\x1b[5m");
				}

				if(attrib & TM_ATTRIB_HIGHLIGHT) {
					append_output("\x1b[7m");
				}

				if(attrib & TM_ATTRIB_HIDDEN) {
					append_output("\x1b[8m");
				}

				if(attrib & TM_ATTRIB_STRIKE) {
					append_output("\x1b[9m");
				}

				if((attrib & TM_ATTRIB_FG_MASK) != 0) {
					append_output("\x1b[%dm", (attrib & TM_ATTRIB_FG_MASK) >> 16);
				}

				if((attrib & TM_ATTRIB_BG_MASK) != 0) {
					append_output("\x1b[%dm", (attrib & TM_ATTRIB_BG_MASK) >> 24);
				}

				if(attrib & TM_ATTRIB_RESET) {
					append_output("\x1b[0m");
				}
			}

			if(disp == '\0') {
				disp = ' ';
			}

			append_output("%c", disp);

			// Make the screen cursor x and y match the last pending change x, y
			screen->cursor_x = i % screen->columns; 
			screen->cursor_y = i / screen->columns;

		}

		screen->physical_buffer[i] = screen->buffer[i];
	}

#ifdef _WIN32
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), screen->output, screen->output_len, &bytes_written, NULL);
#else
	write(fileno(stdout), screen->output, screen->output_len);
#endif

	free(screen->output);
	screen->output = NULL;
	screen->output_len = 0;
}

void tm_win_write_to_screen(Tm_window* win) {
	int parent_x = 0;
	int parent_y = 0;

	if(win->parent != NULL) {
		parent_x = win->parent->position_x;
		parent_y = win->parent->position_y;
	}

	// Update screen flags

	if(win->flags != screen->flags) {
		if(win->flags & TM_FLAG_CURSOR_VISIBLE) {
			append_output("\x1b[?25h");
		}

		else if(win->flags & ~TM_FLAG_CURSOR_VISIBLE) {
			append_output("\x1b[?25l");
		}

		screen->flags = win->flags;
	}

	// Loop through window and if there is a cell in the memory buffer that isn't the same in the physical buffer, insert it in the screens pending changes
	for(int y = 0; y < win->rows; y++) {
		for(int x = 0; x < win->columns; x++) {
			screen->buffer[(win->position_y + parent_y + y) * screen->columns + (win->position_x + parent_x + x)] = win->buffer[y * win->columns + x];
		}	
	}

	for(int i = 0; i < win->children_amount; i++) {
		tm_win_write_to_screen(win->children[i]);
	}
}

void tm_win_update(Tm_window* win) {
	tm_win_write_to_screen(win);
	tm_screen_update();
}
