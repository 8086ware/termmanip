#include "termmanip.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "exit_log.h"
#include "append_win.h"
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
	signal(SIGWINCH, signal_handle);	
	
	int scr_columns, scr_rows;

	tm_get_scrsize(&scr_columns, &scr_rows);

	default_win = malloc(sizeof(Tm_window));

	if(default_win == NULL) {
		exit_log("tm_init", "malloc", 1);
	}

	tm_win_modify(default_win, 0, 0, scr_columns, scr_rows);

	default_win->parent = NULL;
	default_win->children = NULL;

	default_win->children_amount = 0;

	default_win->contents = NULL;
	default_win->content_len = 0;

	default_win->flags = 0;

	append_win(default_win, TM_ESC_ENTER_ALT_SCREEN);
	append_win(default_win, "\x1b[2J");

	tm_win_echo(default_win, 1);
	tm_win_raw(default_win, 1);

	tm_win_cursor(default_win, 0, 0);
	tm_win_attrib(default_win, TM_ATTRIB_RESET);

	tm_update();
}

