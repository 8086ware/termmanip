#include "termmanip.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void tm_init() {
	int scr_columns, scr_rows;

	tm_get_scrsize(&scr_columns, &scr_rows);
	default_win = tm_window(0, 0, scr_columns, scr_rows);
	write(fileno(stdout), TM_ESC_ENTER_ALT_SCREEN, strlen(TM_ESC_ENTER_ALT_SCREEN));
	write(fileno(stdout), "\x1b[2J", strlen("\x1b[2J"));
}

