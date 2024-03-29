#include "termmanip.h"

void tm_win_background(Tm_window* win, char ch, uint32_t attrib) {
	int temp_cursor_x = tm_win_get_cursor_x(win), temp_cursor_y = tm_win_get_cursor_y(win);

	for(int y = 0; y < tm_win_get_buffer_rows(win); y++) {
		for(int x = 0; x < tm_win_get_buffer_columns(win); x++) {
			tm_win_cursor(win, x, y);

			if(win->buffer[y * tm_win_get_buffer_columns(win) + x].disp != win->background_tm_char.disp) {
				if(win->buffer[y * tm_win_get_buffer_columns(win) + x].attrib & TM_ATTRIB_ALTERNATE) {
					tm_win_putch(win, win->buffer[y * tm_win_get_buffer_columns(win) + x].disp, attrib | TM_ATTRIB_ALTERNATE); 
				}
	
				else {
					tm_win_putch(win, win->buffer[y * tm_win_get_buffer_columns(win) + x].disp, attrib); 
				}
			}

			else {
				tm_win_putch(win, ch, attrib); 
			}
		}
	}

	win->background_tm_char.attrib = attrib;
	win->background_tm_char.disp = ch;

	tm_win_attrib(win, TM_ATTRIB_ALL, 0);
	tm_win_attrib(win, tm_win_get_background(win).attrib, 1);

	tm_win_cursor(win, temp_cursor_x, temp_cursor_y);
}
