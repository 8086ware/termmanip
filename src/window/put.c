#include "termmanip.h"
#include <string.h>

int tm_win_putch(Tm_window* win, char ch, uint32_t attrib) {	
	if(win->cursor_y < 0 || win->cursor_y >= win->rows) {
		if(win->flags & TM_FLAG_SCROLL) {
			if(win->cursor_y >= win->rows) {
				tm_win_scroll(win, win->cursor_y - win->rows, TM_SCROLL_DOWN);	
				win->cursor_y -= win->rows; 
				win->cursor_x = 0;
			}
		}

		else {
			tm_error_number = TM_INVALID_CURSOR;		
			return TM_ERROR;
		}
	}

	if(ch == '\n') {
		win->cursor_y++;
		win->cursor_x = 0;
	}

	else {
		win->buffer[win->cursor_y * win->columns + win->cursor_x].attrib = attrib;
		win->buffer[win->cursor_y * win->columns + win->cursor_x].disp = ch;

		win->cursor_x++;
	}	

	int i = win->cursor_y * win->columns + win->cursor_x;

	win->cursor_x = i % win->columns;
	win->cursor_y = i / win->columns;

	win->flags &= ~TM_FLAG_CURSOR_MOVED;

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
