#include "termmanip.h"
#include <stdio.h>
#include <stdlib.h>
#include "screen.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void tm_screen_update() {
	for(int i = 0; i != screen->columns * screen->rows; i++) {
		char disp = screen->buffer[i].disp;
		uint32_t attrib = screen->buffer[i].attrib;

		char physical_disp = screen->physical_buffer[i].disp;
		uint32_t physical_attrib = screen->physical_buffer[i].attrib;

		if(disp != physical_disp || attrib != physical_attrib) {

			// If the screen attribute doesn't match the attribute we want to display then output the new attribute

			terminal_write(i % screen->columns, i / screen->columns, disp, attrib);
		}

	}
	
	append_output("\x1b[%d;%dH", screen->cursor_y + 1, screen->cursor_x + 1);

	write(fileno(stdout), screen->output, screen->output_len);

	free(screen->output);
	screen->output_len = 0;
	screen->output = NULL;
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

	screen->cursor_x = (win->cursor_x - win->buffer_position_x) + win->position_x + parent_x;
	screen->cursor_y = (win->cursor_y - win->buffer_position_y) + win->position_y + parent_y;

	// Loop through window and put its buffer on the screen buffer

	for(int y = 0; y < win->rows; y++) {
		for(int x = 0; x < win->columns; x++) {
			screen->buffer[(win->position_y + parent_y + y) * screen->columns + (win->position_x + parent_x + x)] = win->buffer[(win->buffer_position_y + y) * win->buffer_columns + (win->buffer_position_x + x)];
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
