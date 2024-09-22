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

	// Update win->terminal flags

	if(win->flags != win->terminal->flags) {
		update_terminal_flags(win);
	}

	// Loop through window and put its buffer on the win->terminal buffer

	for(int i = 0; i < win->columns * win->rows; i++) {
		win->physical_buffer[i] = tm_win_get_background(win);
	}

	int wrapped_lines = 0;

	if(win->flags & TM_FLAG_WRAP_TEXT) {
		for(int y = win->buffer_position_y; y < win->buffer_rows; y++) {
			while(((y + wrapped_lines) - win->buffer_position_y) * win->columns < win->columns * win->rows) {
				if(win->physical_buffer[((y + wrapped_lines) - win->buffer_position_y) * win->columns].disp != tm_win_get_background(win).disp || win->physical_buffer[((y + wrapped_lines) - win->buffer_position_y) * win->columns].attrib != tm_win_get_background(win).attrib) {
					wrapped_lines++;
				}

				else {
					break;
				}
			}

			for(int x = win->buffer_position_x; x < win->buffer_columns; x++) {
				if(((y + wrapped_lines) - win->buffer_position_y) * win->columns + (x - win->buffer_position_x) < win->columns * win->rows) {
					Tm_char ch;
					ch.disp = win->buffer[y * tm_win_get_buffer_columns(win) + x].disp;
					ch.attrib = win->buffer[y * tm_win_get_buffer_columns(win) + x].attrib;
					if(ch.disp != tm_win_get_background(win).disp || ch.attrib != tm_win_get_background(win).attrib) {
						win->physical_buffer[(y + wrapped_lines - win->buffer_position_y) * win->columns + (x - win->buffer_position_x)] = ch;
					}
				}
			}
		}
	}

	else {
		for(int y = win->buffer_position_y; y < win->buffer_position_y + win->rows; y++){ 
			for(int x = win->buffer_position_x; x < win->buffer_position_x + win->columns; x++){ 
				win->physical_buffer[(y - win->buffer_position_y) * win->columns + (x - win->buffer_position_x)] = win->buffer[y * win->buffer_columns + x];
			}
		}
	}

	win->terminal->cursor_x = tm_win_get_cursor_x(win) - tm_win_get_buffer_pos_x(win) + tm_win_get_pos_x(win) + parent_x, 
	win->terminal->cursor_y = tm_win_get_cursor_y(win) + wrapped_lines - tm_win_get_buffer_pos_y(win) + tm_win_get_pos_y(win) + parent_y;

	for(int y = 0; y < win->rows; y++) {
		for(int x = 0; x < win->columns; x++) {
			Tm_char ch;
			ch.disp = win->physical_buffer[y * tm_win_get_columns(win) + x].disp;
			ch.attrib = win->physical_buffer[y * tm_win_get_columns(win) + x].attrib;

			terminal_write(win->terminal, (tm_win_get_pos_x(win) + parent_x + x), (tm_win_get_pos_y(win) + parent_y + y), ch.disp, ch.attrib);
		}	
	}

	win->terminal->last_updated_window = win;

	for(int i = 0; i < win->children_amount; i++) {
		tm_win_write_to_terminal(win->children[i]);
	}
}

void tm_win_update(Tm_window* win) {
	tm_win_write_to_terminal(win);
	tm_terminal_update(win->terminal);
}
