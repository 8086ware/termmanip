#include "termmanip.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "screen.h"
#include "error.h"

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
#ifdef _WIN32
	if(SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), og_output_mode) == 0) {
		tm_set_error(TM_ERROR_COULDNT_INIT_TERM);
		return TM_ERROR;
	}

	if(SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), og_input_mode) == 0) {
		tm_set_error(TM_ERROR_COULDNT_INIT_TERM);
		return TM_ERROR;
	}
#else
	tcsetattr(fileno(stdin), TCSANOW, &og_term);
	tcsetattr(fileno(stdout), TCSANOW, &og_term);
#endif

	return 0;
}
