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
	char* buffer = malloc(size);

	vsprintf(buffer, fmt, args);

	va_end(args);

	if((ret = tm_win_puts(win, buffer, win->attrib) == TM_ERROR)) {
		return ret;
	}

	free(buffer);

	return 0;
}

