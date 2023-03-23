#include "append_output.h"
#include "termmanip.h"
#include "exit_log.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

int append_output(Tm_window* win, char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char buffer[strlen(fmt) + 2048];
	vsprintf(buffer, fmt, args);

	va_end(args);
	int len = strlen(buffer);
	win->output = realloc(win->output, win->output_len + len);

	if(win->output == NULL) {
		exit_log("append_output", "realloc", 1);
	}

	for(int i = 0; i < len; i++) {
		win->output[win->output_len + i] = buffer[i];
	}

	win->output_len += len;

	return 0;
}

