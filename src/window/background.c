#include "termmanip.h"
#include "append_win.h"
#include <stdlib.h>
#include <string.h>

void tm_win_background(Tm_window* win, int attrib) {
	char* temp = malloc(win->content_len * sizeof(char));
	int temp_len = win->content_len;
	int cursor_x = win->cursor_x, cursor_y = win->cursor_y;	
	strncpy(temp, win->contents, temp_len);

	tm_win_memclear(win);

	for(int y = 0; y < win->rows; y++) {
		for(int x = 0; x < win->columns; x++) {
			tm_win_cursor(win, x, y);
			tm_win_attrib(win, attrib);
			tm_win_print_ch(win, ' ');
		}
	}

	append_win_str(win, temp, temp_len);

	win->cursor_x = cursor_x;
	win->cursor_y = cursor_y;
}
