#include "termmanip.h"
#include "terminal.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

void terminal_write_win_to_terminal(Tm_window* win, int parent_x, int parent_y) {
	Tm_char* result_buffer = malloc(sizeof(Tm_char) * win->columns * win->rows);

	if (result_buffer == NULL) {
		return;
	}

	if (win->flags & TM_FLAG_SHADOW) {
		for (int y = 1; y < tm_win_get_rows(win); y++) {
			Tm_char ch;
			ch.attrib = TM_ATTRIB_BG_BLACK | TM_ATTRIB_FG_BRIGHTBLACK;
			ch.disp = win->terminal->buffer[(y + tm_win_get_pos_y(win)) * win->terminal->columns + (tm_win_get_columns(win) + tm_win_get_pos_x(win))].disp;

			terminal_write(win->terminal, tm_win_get_pos_x(win) + tm_win_get_columns(win) + parent_x, tm_win_get_pos_y(win) + y + parent_y, ch.disp, ch.attrib);
		}

		for (int x = 1; x < tm_win_get_columns(win) + 1; x++) {
			Tm_char ch;
			ch.attrib = TM_ATTRIB_BG_BLACK | TM_ATTRIB_FG_BRIGHTBLACK;
			ch.disp = win->terminal->buffer[(tm_win_get_rows(win) + tm_win_get_pos_y(win)) * win->terminal->columns + (x + tm_win_get_pos_x(win))].disp;

			terminal_write(win->terminal, tm_win_get_pos_x(win) + x + parent_x, tm_win_get_pos_y(win) + tm_win_get_rows(win) + parent_y, ch.disp, ch.attrib);
		}
	}

	if (win->flags & TM_FLAG_BORDER) {
		for (int i = -1; i < win->columns + 1; i++) {
			terminal_write(win->terminal, parent_x + win->position_x + i, parent_y + win->position_y - 1, '\x71', win->background_tm_char.attrib | TM_ATTRIB_ALTERNATE);
		}

		for (int i = -1; i < win->columns + 1; i++) {
			terminal_write(win->terminal, parent_x + win->position_x + i, parent_y + win->position_y + win->rows, '\x71', win->background_tm_char.attrib | TM_ATTRIB_ALTERNATE);
		}

		for (int i = -1; i < win->rows + 1; i++) {
			terminal_write(win->terminal, parent_x + win->position_x - 1, parent_y + win->position_y + i, '\x78', win->background_tm_char.attrib | TM_ATTRIB_ALTERNATE);
		}

		for (int i = -1; i < win->rows + 1; i++) {
			terminal_write(win->terminal, parent_x + win->position_x + win->columns, parent_y + win->position_y + i, '\x78', win->background_tm_char.attrib | TM_ATTRIB_ALTERNATE);
		}

		terminal_write(win->terminal, parent_x + win->position_x - 1, parent_y + win->position_y - 1, '\x6c', win->background_tm_char.attrib | TM_ATTRIB_ALTERNATE);
		terminal_write(win->terminal, parent_x + win->position_x + win->columns, parent_y + win->position_y - 1, '\x6b', win->background_tm_char.attrib | TM_ATTRIB_ALTERNATE);
		terminal_write(win->terminal, parent_x + win->position_x - 1, parent_y + win->position_y + win->rows, '\x6d', win->background_tm_char.attrib | TM_ATTRIB_ALTERNATE);
		terminal_write(win->terminal, parent_x + win->position_x + win->columns, parent_y + win->position_y + win->rows, '\x6a', win->background_tm_char.attrib | TM_ATTRIB_ALTERNATE);
	}


	for(int i = 0; i < win->columns * win->rows; i++) {
		result_buffer[i] = tm_win_get_background(win);
	}

	win->wrapped_lines = 0;

	if(win->flags & TM_FLAG_WRAP_TEXT) {
		for(int y = win->buffer_position_y; y < win->buffer_rows; y++) {
			while(((y + win->wrapped_lines) - win->buffer_position_y) * win->columns < win->columns * win->rows) {
				// If the beginning of a line in the physical buffer (which is always win->columns * win->rows) has something written to it after 
				// that means the row has wrapped and it will keep checking each extra row if it has wrapped again and increase wrapped_lines

				if(result_buffer[((y + win->wrapped_lines) - win->buffer_position_y) * win->columns].disp != tm_win_get_background(win).disp || result_buffer[((y + win->wrapped_lines) - win->buffer_position_y) * win->columns].attrib != tm_win_get_background(win).attrib) {
					win->wrapped_lines++;
				}

				// If not, break out of the loop checking for it

				else {
					break;
				}
			}
		
			// Write the buffer to the physical buffer depending on how many lines that were wrapped previously
			// For example, if row 0 wrapped once, then write row 1 on row 2, row 2 on row 3 etc

			for(int x = win->buffer_position_x; x < win->buffer_columns; x++) {
				if(((y + win->wrapped_lines) - win->buffer_position_y) * win->columns + (x - win->buffer_position_x) < win->columns * win->rows) {
					Tm_char ch;

					ch.disp = win->buffer[y * tm_win_get_buffer_columns(win) + x].disp;
					ch.attrib = win->buffer[y * tm_win_get_buffer_columns(win) + x].attrib;

					if(ch.disp != tm_win_get_background(win).disp || ch.attrib != tm_win_get_background(win).attrib) {
						result_buffer[(y + win->wrapped_lines - win->buffer_position_y) * win->columns + (x - win->buffer_position_x)] = ch;
					}
				}
			}
		}
	}

	else {
		for(int y = win->buffer_position_y; y < win->buffer_position_y + win->rows; y++){ 
			for(int x = win->buffer_position_x; x < win->buffer_position_x + win->columns; x++){ 
				result_buffer[(y - win->buffer_position_y) * win->columns + (x - win->buffer_position_x)] = win->buffer[y * win->buffer_columns + x];
			}
		}
	}

	// Loop through window and put its buffer on the win->terminal buffer

	for(int y = 0; y < win->rows; y++) {
		for(int x = 0; x < win->columns; x++) {
			Tm_char ch;
			ch.disp = result_buffer[y * tm_win_get_columns(win) + x].disp;
			ch.attrib = result_buffer[y * tm_win_get_columns(win) + x].attrib;

			terminal_write(win->terminal, (tm_win_get_pos_x(win) + parent_x + x), (tm_win_get_pos_y(win) + parent_y + y), ch.disp, ch.attrib);
		}	
	}

	free(result_buffer);
}

