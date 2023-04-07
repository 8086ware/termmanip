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

	screen = NULL;
#ifdef _WIN32
	if(SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), og_output_mode) == 0) {
		exit_log("tm_exit", "SetConsoleMode", 1);
	}

	if(SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), og_input_mode) == 0) {
		exit_log("tm_exit", "SetConsoleMode", 2);
	}
#else
	tcsetattr(fileno(stdin), TCSANOW, &og_term);
	tcsetattr(fileno(stdout), TCSANOW, &og_term);
#endif
	tm_inputblock(1);
}
