#include "terminal.h"
#include "termmanip.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "return.h"

int terminal_append_output(Tm_terminal* terminal, char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	char* buffer = malloc(strlen(fmt) + 2048);
	vsprintf(buffer, fmt, args);

	va_end(args);
	int len = strlen(buffer);

	terminal->output = realloc(terminal->output, terminal->output_len + len);

	if(terminal->output == NULL) {
		tm_set_return(TM_OUT_OF_MEM);
		return TM_ERROR;
	}


	for(int i = 0; i < len; i++) {
		terminal->output[terminal->output_len + i] = buffer[i];
	}

	terminal->output_len += len;
	free(buffer);

	return 0;
}

