#include "termmanip.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int tm_win_print(Tm_window* win, char* fmt, ...) {
	int ret = 0;

	va_list args;

	va_start(args, fmt);

	const int size = strlen(fmt) + 2048;
	char buffer[size];

	vsprintf(buffer, fmt, args);

	va_end(args);

	if((ret = tm_win_puts(win, win->cursor_x, win->cursor_y, buffer, win->attrib) == TM_ERROR)) {
		return ret;
	}

	win->cursor_x += strlen(buffer);

	int i = win->cursor_y * win->columns + win->cursor_x;

	win->cursor_x = i % win->columns;
	win->cursor_y = i / win->columns;

	return 0;
}

