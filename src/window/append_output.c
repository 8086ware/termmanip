#include "append_output.h"
#include "termmanip.h"
#include "exit_log.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

void append_output(char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char buffer[strlen(fmt) + 2048];
	vsprintf(buffer, fmt, args);

	va_end(args);
	int len = strlen(buffer);

	if(screen->output_len + len > screen->alloc_len) {
		screen->output = realloc(screen->output, screen->alloc_len + len);

		if(screen->output == NULL) {
			exit_log("append_output", "realloc", 1);
		}

		screen->alloc_len += len;
	}

	for(int i = 0; i < len; i++) {
		screen->output[screen->output_len + i] = buffer[i];
	}

	screen->output_len += len;
}

