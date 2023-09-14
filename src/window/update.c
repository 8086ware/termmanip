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
		parent_x += tm_win_get_pos_x(parent);
		parent_y += tm_win_get_pos_y(parent);

		parent = parent->parent;
	}

	// Update screen flags

	if(tm_win_get_flags(win) != screen->flags) {
		if(tm_win_get_flags(win) & TM_FLAG_CURSOR_VISIBLE && screen->flags & TM_FLAG_CURSOR_VISIBLE) {
			screen_append_output("\x1b[?25h");
		}

		else if((tm_win_get_flags(win) & TM_FLAG_CURSOR_VISIBLE) != 1 && screen->flags & TM_FLAG_CURSOR_VISIBLE) {
			screen_append_output("\x1b[?25l");
		}

		if(tm_win_get_flags(win) & TM_FLAG_SHADOW) {
			for(int y = 1; y < tm_win_get_rows(win); y++) {
				Tm_char ch;
				ch.attrib = TM_ATTRIB_BG_BLACK | TM_ATTRIB_FG_BRIGHTBLACK;
				ch.disp = screen->buffer[(y + tm_win_get_pos_y(win)) * screen->columns + (tm_win_get_columns(win) + tm_win_get_pos_x(win))].disp;

				screen_buffer_write(tm_win_get_pos_x(win) + tm_win_get_columns(win) + parent_x, tm_win_get_pos_y(win) + y + parent_y, ch);
			}

			for(int x = 1; x < tm_win_get_columns(win) + 1; x++) {
				Tm_char ch;
				ch.attrib = TM_ATTRIB_BG_BLACK | TM_ATTRIB_FG_BRIGHTBLACK;
				ch.disp = screen->buffer[(tm_win_get_rows(win) + tm_win_get_pos_y(win)) * screen->columns + (x + tm_win_get_pos_x(win))].disp;

				screen_buffer_write(tm_win_get_pos_x(win) + x + parent_x, tm_win_get_pos_y(win) + tm_win_get_rows(win) + parent_y, ch);
			}
		}

		screen->flags = tm_win_get_flags(win);
	}

	screen_cursor((tm_win_get_cursor_x(win) - tm_win_get_buffer_pos_x(win)) + tm_win_get_pos_x(win) + parent_x, (tm_win_get_cursor_y(win) - tm_win_get_buffer_pos_y(win)) + tm_win_get_pos_y(win) + parent_y);

	// Loop through window and put its buffer on the screen buffer

	for(int y = 0; y < win->rows; y++) {
		for(int x = 0; x < win->columns; x++) {
			screen_buffer_write((tm_win_get_pos_x(win) + parent_x + x), (tm_win_get_pos_y(win) + parent_y + y), win->buffer[(tm_win_get_buffer_pos_y(win) + y) * tm_win_get_buffer_columns(win) + (tm_win_get_buffer_pos_x(win) + x)]);
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
