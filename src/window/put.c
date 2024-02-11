#include "termmanip.h" 
#include <string.h>
#include "return.h"

void check_for_scroll(Tm_window* win) {
	if(win->flags & TM_FLAG_SCROLL) {
		if(win->cursor_y > tm_win_get_rows(win) - 1 + tm_win_get_buffer_pos_y(win)) {
			tm_win_scroll(win, win->cursor_y - (tm_win_get_rows(win) - 1 + tm_win_get_buffer_pos_y(win)), TM_SCROLL_DOWN);
		}

		else if(win->cursor_y < win->buffer_position_y) {		
			tm_win_scroll(win, tm_win_get_buffer_pos_y(win)- win->cursor_y, TM_SCROLL_UP);
		}

		if(win->cursor_x > tm_win_get_columns(win) - 1 + tm_win_get_buffer_pos_x(win)) {
			tm_win_scroll(win, win->cursor_x - (tm_win_get_columns(win) - 1 + tm_win_get_buffer_pos_x(win)), TM_SCROLL_RIGHT);
		}

		else if(win->cursor_x < win->buffer_position_x) {		
			tm_win_scroll(win, tm_win_get_buffer_pos_x(win)- win->cursor_x, TM_SCROLL_LEFT);
		}
	}
}
int tm_win_putch(Tm_window* win, char ch, uint32_t attrib) {
	int ret = 0;

	check_for_scroll(win);
	_Bool scroll = 0;

	if(ch == '\x1b') {
		return 0;
	}

	else if(ch == '\r') {
		win->cursor_x = 0;
		check_for_scroll(win);
	}

	else if(ch == '\n') {
		win->cursor_y++;
		win->cursor_x = 0;
		check_for_scroll(win);
	}

	else if(ch == '\b' || ch == '\177') {
		win->cursor_x--;
		check_for_scroll(win);
	}

	else if(ch == '\t') {
		win->cursor_x += 4;
		check_for_scroll(win);
	}

	else {
		win->cursor_x++;

		win->buffer[tm_win_get_cursor_y(win) * win->buffer_columns + tm_win_get_cursor_x(win) - 1].attrib = attrib;
		win->buffer[tm_win_get_cursor_y(win) * win->buffer_columns + tm_win_get_cursor_x(win) - 1].disp = ch;
	}

	if(win->cursor_y < 0) {
		win->cursor_y = 0;
	}

	if(win->cursor_x < 0) {
		win->cursor_x = 0;
	}

	if((win->flags & TM_FLAG_SCROLL) == 0) {
		if(win->cursor_x > tm_win_get_buffer_columns(win) - 1) {
			win->cursor_x = tm_win_get_buffer_columns(win) - 1;
		}

		if(win->cursor_y > tm_win_get_buffer_rows(win) - 1) {
			win->cursor_y = tm_win_get_buffer_rows(win) - 1;
		}
	}

	return ret;
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
