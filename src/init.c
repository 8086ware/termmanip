#include "termmanip.h"
#include <stdio.h>
#include <string.h>
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

	int scr_columns, scr_rows;
#endif
	tm_get_scrsize(&scr_columns, &scr_rows);
	default_win = tm_window(0, 0, scr_columns, scr_rows);
	write(fileno(stdout), TM_ESC_ENTER_ALT_SCREEN, strlen(TM_ESC_ENTER_ALT_SCREEN));
	write(fileno(stdout), "\x1b[2J", strlen("\x1b[2J"));
}

