#include "termmanip.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "exit_log.h"
#include "append_output.h"
#include "signal_handler.h"
#include "exit_log.h"
#include <signal.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

void tm_init() {
#ifdef _WIN32
	DWORD mode = 0;

	if(GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &mode) == 0) {
		exit_log("tm_init", "GetConsoleMode", 1);
	}

	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	if(SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), mode) == 0) {
		exit_log("tm_init", "SetConsoleMode", 1);
	}

	if(GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode) == 0) {
		exit_log("tm_init", "GetConsoleMode", 1);
	}

	mode &= ~ENABLE_ECHO_INPUT;
	mode &= ~ENABLE_LINE_INPUT;

	if(SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode) == 0) {
		exit_log("tm_init", "SetConsoleMode", 1);
	}


#else 
	struct termios term;
	tcgetattr(fileno(stdin), &term);

	term.c_lflag &= ~ECHO;
	term.c_lflag &= ~ICANON;

	tcsetattr(fileno(stdin), TCSANOW, &term);
#endif
	signal(SIGINT, signal_handle);
	signal(SIGABRT, signal_handle);
	signal(SIGSEGV, signal_handle);
	signal(SIGTERM, signal_handle);
	signal(SIGILL, signal_handle);	
#ifdef _WIN32
#else
	signal(SIGWINCH, signal_handle);	
#endif	
	int scr_columns = 0, scr_rows = 0;

	tm_get_scrsize(&scr_columns, &scr_rows);

	default_win = tm_window(0, 0, scr_columns, scr_rows);

	char init[] = "\x1b[?1049h\x1b[2J";

	write(fileno(stdout), init, strlen(init));
}

