#include "termmanip.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "screen.h"
#include "error.h"
#include "term.h"

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

int tm_exit() {
	char exit[] = "\x1b[0m\x1b(B\x1b[?25h\x1b[?1049l";

	write(fileno(stdout), exit, strlen(exit));

	if(tm_win_free(default_win) == TM_ERROR) {
		return TM_ERROR;	
	}

	screen_free();
	term_exit();
	return 0;
}
