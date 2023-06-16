#include "termmanip.h"
#include "signal_handler.h"
#include <signal.h>
#include "exit_log.h"
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
DWORD og_input_mode;
DWORD og_output_mode;
#else
#include <termios.h>
struct termios og_term;
#endif

void term_init() {
#ifdef _WIN32
	DWORD mode = 0;

	if(GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &mode) == 0) {
		exit_log("term_init", "GetConsoleMode", 1);
	}

	og_output_mode = mode;

	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	if(SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), mode) == 0) {
		exit_log("term_init", "SetConsoleMode", 1);
	}

	if(GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode) == 0) {
		exit_log("term_init", "GetConsoleMode", 2);
	}

	og_input_mode = mode;

	mode &= ~ENABLE_ECHO_INPUT;
	mode &= ~ENABLE_LINE_INPUT;

	if(SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode) == 0) {
		exit_log("termm_init", "SetConsoleMode", 2);
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
#ifdef _WIN32
#else
	signal(SIGWINCH, signal_handle);	
#endif	
}
