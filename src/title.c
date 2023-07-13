#include "termmanip.h"
#include <stdio.h>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

void tm_set_title(char* text) {
	char buffer[2048];
	
	int bytes_written = sprintf(buffer, "\x1b]0;%s", text);

	write(fileno(stdout), buffer, bytes_written);
}
