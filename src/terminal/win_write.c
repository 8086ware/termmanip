#include "termmanip.h"
#include "terminal.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

void terminal_write_win_to_terminal(Tm_window* win, int parent_x, int parent_y) {
	// Update win->terminal flags

	if(win->flags != win->terminal->flags) {
		update_terminal_flags(win);
	}

	for(int i = 0; i < win->columns * win->rows; i++) {
		win->physical_buffer[i] = tm_win_get_background(win);
	}

	int wrapped_lines = 0;

	if(win->flags & TM_FLAG_WRAP_TEXT) {
		for(int y = win->buffer_position_y; y < win->buffer_rows; y++) {
			while(((y + wrapped_lines) - win->buffer_position_y) * win->columns < win->columns * win->rows) {
				// If the beginning of a line in the physical buffer (which is always win->columns * win->rows) has something written to it after 
				// that means the row has wrapped and it will keep checking each extra row if it has wrapped again and increase wrapped_lines

				if(win->physical_buffer[((y + wrapped_lines) - win->buffer_position_y) * win->columns].disp != tm_win_get_background(win).disp || win->physical_buffer[((y + wrapped_lines) - win->buffer_position_y) * win->columns].attrib != tm_win_get_background(win).attrib) {
					wrapped_lines++;
				}

				// If not, break out of the loop checking for it

				else {
					break;
				}
			}
		
			// Write the buffer to the physical buffer depending on how many lines that were wrapped previously
			// For example, if row 0 wrapped once, then write row 1 on row 2, row 2 on row 3 etc

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

	// Loop through window and put its buffer on the win->terminal buffer

	for(int y = 0; y < win->rows; y++) {
		for(int x = 0; x < win->columns; x++) {
			Tm_char ch;
			ch.disp = win->physical_buffer[y * tm_win_get_columns(win) + x].disp;
			ch.attrib = win->physical_buffer[y * tm_win_get_columns(win) + x].attrib;

			terminal_write(win->terminal, (tm_win_get_pos_x(win) + parent_x + x), (tm_win_get_pos_y(win) + parent_y + y), ch.disp, ch.attrib);
		}	
	}
}

