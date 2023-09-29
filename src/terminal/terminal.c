#include "termmanip.h"
#include "terminal.h"
#include <stdlib.h>
#include "error.h"
#include <stdio.h>
#include "signal_handler.h"
#include <signal.h>

#ifdef _WIN32
#include <windows.h>
DWORD og_input_mode;
DWORD og_output_mode;
#else
#include <termios.h>
#include <sys/signalfd.h>
struct termios og_term;
#endif

int terminal_init() {
	int scr_columns, scr_rows;
	tm_get_scrsize(&scr_columns, &scr_rows);
	terminal = malloc(sizeof(Tm_terminal));

	if(terminal == NULL) {
		tm_set_error(TM_OUT_OF_MEM);
		return TM_ERROR;
	}

	terminal->columns = scr_columns;
	terminal->rows = scr_rows;

	terminal->cursor_x = 0;
	terminal->cursor_y = 0;

	terminal->last_updated_x = 0;
	terminal->last_updated_y = 0;

	terminal->output = NULL;
	terminal->output_len = 0;

	terminal->attrib = 0;

	terminal->flags = TM_FLAG_CURSOR_VISIBLE | TM_FLAG_ECHO;

	terminal->buffer = malloc(sizeof(Tm_char) * terminal->columns * terminal->rows);

	if(terminal->buffer == NULL) {
		tm_set_error(TM_OUT_OF_MEM);
		return TM_ERROR;
	}	

	for(int i = 0; i < terminal->columns * terminal->rows; i++) {
		terminal->buffer[i].disp = ' ';
		terminal->buffer[i].attrib = 0;
	}
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

	mode |= ENABLE_VIRTUAL_TERMINAL_INPUT;

	if(SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode) == 0) {
		tm_set_error(TM_ERROR_COULDNT_INIT_TERM);
		return TM_ERROR;
	}

	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
#else 
	struct termios term;
	tcgetattr(fileno(stdin), &term);
	og_term = term;

	term.c_lflag &= ~ECHO;
	term.c_lflag &= ~ICANON;

	tcsetattr(fileno(stdin), TCSANOW, &term);
#endif
	signal(SIGINT, signal_handle);
#ifndef _WIN32
	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask, SIGWINCH);

	sigprocmask(SIG_BLOCK, &mask, NULL);
	terminal->signal_fd = signalfd(-1, &mask, 0);

	if(terminal->signal_fd == -1) {
		tm_set_error(TM_ERROR_COULDNT_INIT_TERM);
		return TM_ERROR;
	}
#endif

	return 0;
}

int terminal_free() {
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

	close(terminal->signal_fd);
	free(terminal->buffer);
	free(terminal->output);
	free(terminal);

	terminal = NULL;
	return 0;
}
