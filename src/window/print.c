#include "termmanip.h"
#include "append_win.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int handle_escape_codes(Tm_window* win, char escape) {
	int ret = 0;

	switch(escape) {
	case '\n': {
		   if((ret = tm_win_cursor(win, 0, win->cursor_y + 1)) == TM_ERROR) {
			   return ret;
		   }

		   break;
	}
	}
	
	return 0;
}

int check_wrap_line(Tm_window* win) {
	int ret = 0;

	if(win->cursor_x >= win->columns) {
		if((ret = tm_win_cursor(win, 0, win->cursor_y + 1)) == TM_ERROR) {
			return ret;
		}
	}

	return 0;
}

int tm_win_print(Tm_window* win, char* fmt, ...) {
	int ret = 0;

	va_list args;

	va_start(args, fmt);

	char buffer[4096];

	vsprintf(buffer, fmt, args);

	va_end(args);

	for(int i = 0; buffer[i] != '\0'; i++) {
		if((ret = check_wrap_line(win)) == TM_ERROR) {
			return ret;
		}

		if(buffer[i] == '\n' || buffer[i] == '\b') {
			if((ret = handle_escape_codes(win, buffer[i])) == TM_ERROR) {
				return ret;
			}
			continue;
		}
	
		if((ret = append_win(win, "%c", buffer[i])) == TM_ERROR) {
			return ret;
		}

		win->cursor_x++;
	}
	
	return 0;
}

