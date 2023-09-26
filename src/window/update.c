#include "termmanip.h"
#include <stdio.h>
#include <stdlib.h>
#include "terminal.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

void tm_win_write_to_terminal(Tm_window* win) {
	int parent_x = 0;
	int parent_y = 0;

	Tm_window* parent = win->parent;

	while(parent != NULL) {	
		parent_x += tm_win_get_pos_x(parent);
		parent_y += tm_win_get_pos_y(parent);

		parent = parent->parent;
	}

	// Update terminal flags

	if(tm_win_get_flags(win) != terminal->flags) {
		if(tm_win_get_flags(win) & TM_FLAG_CURSOR_VISIBLE && terminal->flags & TM_FLAG_CURSOR_VISIBLE) {
			terminal_append_output("\x1b[?25h");
		}

		else if((tm_win_get_flags(win) & TM_FLAG_CURSOR_VISIBLE) == 0 && terminal->flags & TM_FLAG_CURSOR_VISIBLE) {
			terminal_append_output("\x1b[?25l");
		}

		if(tm_win_get_flags(win) & TM_FLAG_SHADOW) {
			for(int y = 1; y < tm_win_get_rows(win); y++) {
				Tm_char ch;
				ch.attrib = TM_ATTRIB_BG_BLACK | TM_ATTRIB_FG_BRIGHTBLACK;
				ch.disp = terminal->buffer[(y + tm_win_get_pos_y(win)) * terminal->columns + (tm_win_get_columns(win) + tm_win_get_pos_x(win))].disp;

				terminal_buffer_write(tm_win_get_pos_x(win) + tm_win_get_columns(win) + parent_x, tm_win_get_pos_y(win) + y + parent_y, ch);
			}

			for(int x = 1; x < tm_win_get_columns(win) + 1; x++) {
				Tm_char ch;
				ch.attrib = TM_ATTRIB_BG_BLACK | TM_ATTRIB_FG_BRIGHTBLACK;
				ch.disp = terminal->buffer[(tm_win_get_rows(win) + tm_win_get_pos_y(win)) * terminal->columns + (x + tm_win_get_pos_x(win))].disp;

				terminal_buffer_write(tm_win_get_pos_x(win) + x + parent_x, tm_win_get_pos_y(win) + tm_win_get_rows(win) + parent_y, ch);
			}
		}

		terminal->flags = tm_win_get_flags(win);
	}

	terminal_cursor((tm_win_get_cursor_x(win) - tm_win_get_buffer_pos_x(win)) + tm_win_get_pos_x(win) + parent_x, (tm_win_get_cursor_y(win) - tm_win_get_buffer_pos_y(win)) + tm_win_get_pos_y(win) + parent_y);

	// Loop through window and put its buffer on the terminal buffer

	for(int y = 0; y < win->rows; y++) {
		for(int x = 0; x < win->columns; x++) {
			terminal_buffer_write((tm_win_get_pos_x(win) + parent_x + x), (tm_win_get_pos_y(win) + parent_y + y), win->buffer[(tm_win_get_buffer_pos_y(win) + y) * tm_win_get_buffer_columns(win) + (tm_win_get_buffer_pos_x(win) + x)]);
		}	
	}

	for(int i = 0; i < win->children_amount; i++) {
		tm_win_write_to_terminal(win->children[i]);
	}
}

void tm_win_update(Tm_window* win) {
	tm_win_write_to_terminal(win);
	tm_terminal_update();
}
