#include "termmanip.h" 
#include <string.h>

int tm_win_putch(Tm_window* win, char ch, uint32_t attrib) {
	int position = win->cursor_y * win->columns + win->cursor_x;

	if(win->flags & TM_FLAG_SCROLL) {
		if(win->cursor_y > win->rows - 1 + win->buffer_position_y) {
			tm_win_scroll(win, win->cursor_y - (win->rows - 1 + win->buffer_position_y), TM_SCROLL_DOWN);
		}

		else if(win->cursor_y < win->buffer_position_y) {		
			tm_win_scroll(win, win->buffer_position_y - win->cursor_y, TM_SCROLL_UP);
		}
	}

	else if(win->cursor_y > win->buffer_rows - 1 || win->cursor_y < 0) {
		tm_error_number = TM_INVALID_CURSOR;
		return TM_ERROR;
	}


	if(ch == '\n') {
		win->cursor_y++;
		win->cursor_x = 0;
	}

	else {
		win->buffer[win->cursor_y * win->buffer_columns + win->cursor_x].attrib = attrib;
		win->buffer[win->cursor_y * win->buffer_columns + win->cursor_x].disp = ch;

		win->cursor_x++;
	}

	position = win->cursor_y * win->columns + win->cursor_x;

	win->cursor_x = position % win->columns;
	win->cursor_y = position / win->columns;

	return 0;
}

int tm_win_puts(Tm_window* win, char* str, uint32_t attrib) {
	int ret = 0;

	for(; *str != '\0'; str++) {
		if((ret = tm_win_putch(win, *str, attrib)) == TM_ERROR) {
			return ret;
		}
	}

	return 0;
}
