#include "termmanip.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "exit_log.h"
#include "append_win.h"
#include "signal_handler.h"
#include <signal.h>
#include <termios.h>
#include <unistd.h>

void tm_init() {
	signal(SIGINT, signal_handle);
	signal(SIGABRT, signal_handle);
	signal(SIGSEGV, signal_handle);
	signal(SIGTERM, signal_handle);
	signal(SIGILL, signal_handle);	

	int scr_columns, scr_rows;

	tm_get_scrsize(&scr_columns, &scr_rows);
	default_win = tm_window(0, 0, scr_columns, scr_rows);

	write(fileno(stdout), TM_ESC_ENTER_ALT_SCREEN, strlen(TM_ESC_ENTER_ALT_SCREEN));
	write(fileno(stdout), "\x1b[2J", strlen("\x1b[2J"));

	struct termios term;
	tcgetattr(fileno(stdin), &term);

	term.c_lflag &= ~ECHO;
	term.c_lflag &= ~ICANON;

	tcsetattr(fileno(stdin), TCSANOW, &term);
}

