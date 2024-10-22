#include "terminal.h"
#include "termmanip.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "return.h"

int terminal_append_output(Tm_terminal* terminal, char* fmt, ...) {
	va_list args_len;
	va_list args_output;

	va_start(args_len, fmt);
	va_copy(args_output, args_len);

	int len = vsnprintf(NULL, 0, fmt, args_len);

	va_end(args_len);

	len++; // Include null terminator because vsnprintf

	terminal->output = realloc(terminal->output, terminal->output_len + len);

	if(terminal->output == NULL) {
		tm_set_return(terminal, TM_OUT_OF_MEM);
		return TM_ERROR;
	}

	vsnprintf(&terminal->output[terminal->output_len], len, fmt, args_output);

	va_end(args_output);

	terminal->output_len += len - 1; // Negative 1 because we will overwrite the added null terminator next call
	return 0;
}

