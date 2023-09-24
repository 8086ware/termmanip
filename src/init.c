#include "termmanip.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "screen.h"
#include "term.h"

#ifndef _WIN32
#include <unistd.h>
#else
#include <io.h>
#endif

Tm_screen* screen = NULL;

int tm_init() {
	if(screen_init() == TM_ERROR) {
		return TM_ERROR;
	}
	if(term_init() == TM_ERROR) {
		return TM_ERROR;
	}


	int scr_columns = 0, scr_rows = 0;
	tm_get_scrsize(&scr_columns, &scr_rows);

	default_win = tm_window(0, 0, scr_columns, scr_rows);

	if(default_win == NULL) {
		return TM_ERROR;
	}

	char init[] = "\x1b[?1049h\x1b[2J\x1b[H\x1b[0m";

	write(fileno(stdout), init, strlen(init));

	return 0;
}

