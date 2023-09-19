#include "termmanip.h"
#include "signal_handler.h"
#include <signal.h>
#include "error.h"
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
DWORD og_input_mode;
DWORD og_output_mode;
#else
#include <termios.h>
struct termios og_term;
#endif

int term_init() {
#ifdef _WIN32
	DWORD mode = 0;

	if(GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &mode) == 0) {
		tm_set_error(TM_ERROR_COULDNT_INIT_TERM);
		return TM_ERROR;
	}

	og_output_mode = mode;

	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	if(SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), mode) == 0) {
		tm_set_error(TM_ERROR_COULDNT_INIT_TERM);
		return TM_ERROR;
	}

	if(GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode) == 0) {
		tm_set_error(TM_ERROR_COULDNT_INIT_TERM);
		return TM_ERROR;
	}

	og_input_mode = mode;

	mode &= ~ENABLE_ECHO_INPUT;
	mode &= ~ENABLE_LINE_INPUT;
	mode &= ~ENABLE_WINDOW_INPUT;
	mode &= ~ENABLE_MOUSE_INPUT;

	mode |= ENABLE_VIRTUAL_TERMINAL_INPUT;

	if(SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode) == 0) {
		tm_set_error(TM_ERROR_COULDNT_INIT_TERM);
		return TM_ERROR;
	}
#else 
	struct termios term;
	tcgetattr(fileno(stdin), &term);
	og_term = term;

	term.c_lflag &= ~ECHO;
	term.c_lflag &= ~ICANON;

	tcsetattr(fileno(stdin), TCSANOW, &term);
#endif
	signal(SIGINT, signal_handle);
	signal(SIGTERM, signal_handle);
	return 0;
}

int term_exit() {
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
