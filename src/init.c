#include "termmanip.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "exit_log.h"
#include "append_win.h"

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#else
#include <unistd.h>
#endif

void tm_init() {
#ifdef _WIN32
	DWORD console_mode = 0;

	GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &console_mode);

	console_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), console_mode);
#endif
	int scr_columns, scr_rows;

	tm_get_scrsize(&scr_columns, &scr_rows);

	default_win = malloc(sizeof(Tm_window));

	if(default_win == NULL) {
		exit_log("tm_window", "malloc", 1);
	}

	tm_win_modify(default_win, 0, 0, scr_columns, scr_rows);

	default_win->parent = NULL;
	default_win->children = NULL;

	default_win->children_amount = 0;

	default_win->contents = NULL;
	default_win->content_len = 0;
	
	append_win(default_win, TM_ESC_ENTER_ALT_SCREEN);
	append_win(default_win, "\x1b[2J");

	tm_win_cursor(default_win, 0, 0);
	tm_echo(0);
}

