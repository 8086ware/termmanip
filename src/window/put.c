#include "termmanip.h" 
#include <string.h>

int tm_win_putch(Tm_window* win, char ch, uint32_t attrib) {	
	int position = win->cursor_y * win->columns + win->cursor_x;

	if(position < 0 || position >= win->columns * win->rows) {
		if(win->flags & TM_FLAG_SCROLL) {
			if(position >= win->columns * win->rows) {
				tm_win_scroll(win, (1 + (position / win->columns) - win->rows), TM_SCROLL_DOWN);	
			}
		}

		else {
			tm_error_number = TM_INVALID_CURSOR;		
			return TM_ERROR;
		}

		position = win->cursor_y * win->columns + win->cursor_x;
	}

	if(ch == '\n') {
		win->cursor_y++;
		win->cursor_x = 0;
	}

	else {
		win->buffer[position].attrib = attrib;
		win->buffer[position].disp = ch;

		win->cursor_x++;
	}

	position = win->cursor_y * win->columns + win->cursor_x;

	win->cursor_x = position % win->columns;
	win->cursor_y = position / win->columns;

	return 0;
}

int tm_win_puts(Tm_window* win, char* str, uint32_t attrib) {
	int ret = 0;

	for(int i = 0; i < strlen(str); i++) {
		if((ret = tm_win_putch(win, str[i], attrib)) == TM_ERROR) {
			return ret;
		}
	}

	return 0;
}
