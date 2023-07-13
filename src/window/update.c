#include "termmanip.h"
#include <stdio.h>
#include <stdlib.h>
#include "screen.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

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
		if(win->flags & TM_FLAG_CURSOR_VISIBLE && screen->flags & ~TM_FLAG_CURSOR_VISIBLE) {
			screen_append_output("\x1b[?25h");
		}

		else if(win->flags & ~TM_FLAG_CURSOR_VISIBLE && screen->flags & TM_FLAG_CURSOR_VISIBLE) {
			screen_append_output("\x1b[?25l");
		}

#ifndef _WIN32
		if((win->flags & TM_FLAG_INPUTBLOCK) == 0 && screen->flags & TM_FLAG_INPUTBLOCK) {
			struct termios term;
			tcgetattr(fileno(stdout), &term); 
			term.c_cc[VMIN] = 0;
			term.c_cc[VTIME] = 0;
			tcsetattr(fileno(stdout), TCSANOW, &term);
		}

		else if(win->flags & TM_FLAG_INPUTBLOCK && (screen->flags & TM_FLAG_INPUTBLOCK) == 0) {
			struct termios term;
			tcgetattr(fileno(stdout), &term); 
			term.c_cc[VMIN] = 1;
			term.c_cc[VTIME] = 0;
			tcsetattr(fileno(stdout), TCSANOW, &term);
		}
#endif
		
		if(win->flags & TM_FLAG_SHADOW) {
			for(int y = 1; y < win->rows; y++) {
				Tm_char ch;
				ch.attrib = TM_ATTRIB_BG_BLACK | TM_ATTRIB_FG_BRIGHTBLACK;
				ch.disp = screen->buffer[(y + win->position_y) * screen->columns + (win->columns + win->position_x)].disp;

				screen_buffer_write(win->position_x + win->columns, win->position_y + y, ch);
			}

			for(int x = 1; x < win->columns + 1; x++) {
				Tm_char ch;
				ch.attrib = TM_ATTRIB_BG_BLACK | TM_ATTRIB_FG_BRIGHTBLACK;
				ch.disp = screen->buffer[(win->rows + win->position_y) * screen->columns + (x + win->position_x)].disp;

				screen_buffer_write(win->position_x + x, win->position_y + win->rows, ch);
			}
		}

		screen->flags = win->flags;
	}

	screen_cursor((win->cursor_x - win->buffer_position_x) + win->position_x + parent_x, (win->cursor_y - win->buffer_position_y) + win->position_y + parent_y);

	// Loop through window and put its buffer on the screen buffer

	for(int y = 0; y < win->rows; y++) {
		for(int x = 0; x < win->columns; x++) {
			screen_buffer_write((win->position_x + parent_x + x), (win->position_y + parent_y + y), win->buffer[(win->buffer_position_y + y) * win->buffer_columns + (win->buffer_position_x + x)]);
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
