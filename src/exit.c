#include "termmanip.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#endif

void tm_exit() {
	char exit[] = "\x1b[0m\x1b[?25h\x1b[?1049l";

	write(fileno(stdout), exit, strlen(exit));

	tm_win_free(default_win);

	free(screen->output);
	free(screen);

#ifdef _WIN32
	DWORD mode = 0;

	if(GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &mode) == 0) {
		exit_log("tm_init", "SetConsoleMode", 1);
	}

	mode &= ~ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	if(SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), mode) == 0) {
		exit_log("tm_exit", "SetConsoleMode", 1);
	}

	if (GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode) == 0) {
		exit_log("tm_exit", "SetConsoleMode", 1);
	}

	mode |= ENABLE_LINE_INPUT;
	mode |= ENABLE_ECHO_INPUT;

	if(SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode) == 0) {
		exit_log("tm_exit", "SetConsoleMode", 1);
	}
#else
	struct termios term;
	tcgetattr(fileno(stdin), &term);

	term.c_lflag |= ECHO;
	term.c_lflag |= ICANON;

	tcsetattr(fileno(stdin), TCSANOW, &term);
#endif
	tm_inputblock(1);
}
