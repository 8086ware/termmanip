#include "screen.h"
#include "termmanip.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "error.h"

int screen_append_output(char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char* buffer = malloc(strlen(fmt) + 2048);
	vsprintf(buffer, fmt, args);

	va_end(args);
	int len = strlen(buffer);

	screen->output = realloc(screen->output, screen->output_len + len);

	if(screen->output == NULL) {
		tm_set_error(TM_OUT_OF_MEM);
		return TM_ERROR;
	}


	for(int i = 0; i < len; i++) {
		screen->output[screen->output_len + i] = buffer[i];
	}

	screen->output_len += len;
	free(buffer);

	return 0;
}

