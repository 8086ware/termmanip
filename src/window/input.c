#include "termmanip.h"
#include <unistd.h>
#include <stdio.h>
#include "append_win.h"

int tm_win_input_ch(Tm_window* win) {
	int ret = 0;
	char ch[4096];

	if(win->flags & TM_FLAG_RAW) {	
		read(fileno(stdin), ch, 1);

		if(win->flags & TM_FLAG_ECHO) {
			if((ret = tm_win_print(win, "%c", *ch)) == TM_ERROR) {
				return TM_ERROR;
			}

			tm_win_update(win);
		}
	}

	else {
		if((ret = tm_win_input_str(win, ch, 4096)) == TM_ERROR) {
			return ret;
		}
	}

	return *ch;
}

int tm_win_input_str(Tm_window* win, char* str, int max_size) { 
	int i = 0;
	int ch = 0;

	int ret = 0;

	while(1) {
		read(fileno(stdin), &ch, 1);

		if(ch == '\n') {
			break;
		}

		if(ch == '\177') {
			if(i > 0) {
				str[i] = '\0';
				i--;
			}

			else {
				continue;
			}

			int tempX = win->cursor_x;
			int tempY = win->cursor_y;

			if((ret = tm_win_cursor(win, win->cursor_x - 1, win->cursor_y)) == TM_ERROR) {
				return ret;
			}

			if((ret = append_win(win, " ")) == TM_ERROR) {
				return ret;
			}

			if((ret = tm_win_cursor(win, tempX - 1, tempY)) == TM_ERROR) {
				return ret;
			}

			tm_win_update(win);

			continue;
		}

		if((ret = tm_win_print(win, "%c", ch)) == TM_ERROR) {
			continue;
		}

		if(i <= max_size) {
			str[i] = ch;
			i++;
		}

		tm_win_update(win);
	}

	str[i] = '\0';

	return 0;
}
