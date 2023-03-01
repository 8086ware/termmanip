#include "append_win.h"
#include "termmanip.h"
#include "exit_log.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

int append_win(Tm_window* win, char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char buffer[4096];
	vsprintf(buffer, fmt, args);

	int len = strlen(buffer);
	win->contents = realloc(win->contents, win->content_len + len);

	if(win->contents == NULL) {
		exit_log("append_win", "realloc", 1);
	}

	for(int i = 0; i < len; i++) {
		win->contents[win->content_len + i] = buffer[i];
	}

	win->content_len += len;

	va_end(args);

	return 0;
}

