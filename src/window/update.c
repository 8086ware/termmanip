#include "termmanip.h"
#include <stdio.h>
#include "append_output.h"
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
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
				if(attrib & TM_ATTRIB_ALTERNATE && (screen->attrib & TM_ATTRIB_ALTERNATE) == 0) {
					append_output("\x1b(0");
				}

				else if((attrib & TM_ATTRIB_ALTERNATE) == 0 && screen->attrib & TM_ATTRIB_ALTERNATE) {
					append_output("\x1b(B");
				}

				if(attrib & TM_ATTRIB_BOLD && (screen->attrib & TM_ATTRIB_BOLD) == 0) {
					append_output("\x1b[1m");
				}

				else if((attrib & TM_ATTRIB_BOLD) == 0 && screen->attrib & TM_ATTRIB_BOLD) {
					append_output("\x1b[22m");
				}

				if(attrib & TM_ATTRIB_DIM && (screen->attrib & TM_ATTRIB_DIM) == 0) {
					append_output("\x1b[2m");
				}

				else if((attrib & TM_ATTRIB_DIM) == 0 && screen->attrib & TM_ATTRIB_DIM) {
					append_output("\x1b[22m");
				}

				if(attrib & TM_ATTRIB_ITALIC && (screen->attrib & TM_ATTRIB_ITALIC) == 0) {
					append_output("\x1b[3m");
				}

				else if((attrib & TM_ATTRIB_ITALIC) == 0 && screen->attrib & TM_ATTRIB_ITALIC) {
					append_output("\x1b[23m");
				}

				if(attrib & TM_ATTRIB_UNDERLINE && (screen->attrib & TM_ATTRIB_UNDERLINE) == 0) {
					append_output("\x1b[4m");
				}

				else if((attrib & ~TM_ATTRIB_UNDERLINE) == 0 && screen->attrib & TM_ATTRIB_UNDERLINE) {
					append_output("\x1b[24m");
				}

				if(attrib & TM_ATTRIB_BLINKING && (screen->attrib & TM_ATTRIB_BLINKING) == 0) {
					append_output("\x1b[5m");
				}

				else if((attrib & TM_ATTRIB_BLINKING) == 0 && screen->attrib & TM_ATTRIB_BLINKING) {
					append_output("\x1b[25m");
				}

				if(attrib & TM_ATTRIB_HIGHLIGHT && (screen->attrib & TM_ATTRIB_HIGHLIGHT) == 0) {
					append_output("\x1b[7m");
				}

				else if((attrib & TM_ATTRIB_HIGHLIGHT) == 0 && screen->attrib & TM_ATTRIB_HIGHLIGHT) {
					append_output("\x1b[27m");
				}

				if(attrib & TM_ATTRIB_HIDDEN && (screen->attrib & TM_ATTRIB_HIDDEN) == 0) {
					append_output("\x1b[8m");
				}

 				else if((attrib & TM_ATTRIB_HIDDEN) == 0 && screen->attrib & TM_ATTRIB_HIDDEN) {
					append_output("\x1b[28m");
				}
 
				if(attrib & TM_ATTRIB_STRIKE && (screen->attrib & TM_ATTRIB_STRIKE) == 0) {
					append_output("\x1b[9m");
				}

 				else if((attrib & TM_ATTRIB_STRIKE) == 0 && screen->attrib & TM_ATTRIB_STRIKE) {
					append_output("\x1b[29m");
				}

				if(attrib & TM_ATTRIB_FG_MASK && (screen->attrib & TM_ATTRIB_FG_MASK) != (attrib & TM_ATTRIB_FG_MASK)) {
					append_output("\x1b[%dm", (attrib & TM_ATTRIB_FG_MASK) >> 16);
				}
				
				else if((attrib & TM_ATTRIB_FG_MASK) == 0 && (screen->attrib & TM_ATTRIB_FG_MASK) != 0) {
					append_output("\x1b[39m");
				}

				if(attrib & TM_ATTRIB_BG_MASK && (screen->attrib & TM_ATTRIB_BG_MASK) != (attrib & TM_ATTRIB_BG_MASK)) {
					append_output("\x1b[%dm", (attrib & TM_ATTRIB_BG_MASK) >> 24);
				}

				else if((attrib & TM_ATTRIB_BG_MASK) == 0 && (screen->attrib & TM_ATTRIB_BG_MASK) != 0) {
					append_output("\x1b[49m");
				}

				screen->attrib = attrib;
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

	write(fileno(stdout), screen->output, screen->output_len);

	free(screen->output);
	screen->output = NULL;
	screen->output_len = 0;
}

void tm_win_write_to_screen(Tm_window* win) {
	int parent_x = 0;
	int parent_y = 0;
	
	Tm_window* parent = win->parent;
	while(parent != NULL) {	
		parent_x += parent->position_x;
		parent_y += parent->position_y;
	
		parent = parent->parent;
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

	// Loop through window and put its buffer on the screen buffer
	
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
