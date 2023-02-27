#include "termmanip.h"
#include "append_win.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void handle_escape_codes(Tm_window* win, char escape) {
	switch(escape) {
	case '\n': {
		tm_win_cursor(win, 0, win->cursor_y + 1);
		break;
	}
	}

}

int check_wrap_line(Tm_window* win) {
	int ret = 0;

	if(win->cursor_x >= win->columns) {
		if((ret = tm_win_cursor(win, 0, win->cursor_y + 1))) {
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

	for(int i = 0; buffer[i] != '\0'; i++) {
		if((ret = check_wrap_line(win))) {
			return ret;
		}
	
		if(buffer[i] == '\n' || buffer[i] == '\b') {
			handle_escape_codes(win, *buffer);
			return 0;
		}

		append_win(win, "%c", buffer[i]);

		win->cursor_x++;
	}

	va_end(args);
	return 0;
}

