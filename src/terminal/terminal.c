#include "termmanip.h"
#include "terminal.h"
#include <stdlib.h>
#include "return.h"
#include <stdio.h>
#include "signal_handler.h"
#include <signal.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
DWORD og_input_mode;
DWORD og_output_mode;
#else
#include <termios.h>
#include <sys/signalfd.h>
#include <unistd.h>
struct termios og_term;
#endif

int terminal_init() {
	int scr_columns, scr_rows;
	tm_get_scrsize(&scr_columns, &scr_rows);
	terminal = malloc(sizeof(Tm_terminal));

	if(terminal == NULL) {
		tm_set_return(TM_OUT_OF_MEM);
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

	terminal->resized = 0;

	terminal->buffer = malloc(sizeof(Tm_char) * terminal->columns * terminal->rows);

	if(terminal->buffer == NULL) {
		tm_set_return(TM_OUT_OF_MEM);
		return TM_ERROR;
	}	

	for(int i = 0; i < terminal->columns * terminal->rows; i++) {
		terminal->buffer[i].disp = ' ';
		terminal->buffer[i].attrib = 0;
	}
#ifdef _WIN32
	DWORD mode = 0;

	if(GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &mode) == 0) {
		tm_set_return(TM_COULDNT_INIT_TERM);
		return TM_ERROR;
	}

	og_output_mode = mode;

	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	if(SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), mode) == 0) {
		tm_set_return(TM_COULDNT_INIT_TERM);
		return TM_ERROR;
	}

	if(GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode) == 0) {
		tm_set_return(TM_COULDNT_INIT_TERM);
		return TM_ERROR;
	}

	og_input_mode = mode;

	mode &= ~ENABLE_ECHO_INPUT;
	mode &= ~ENABLE_LINE_INPUT;

	mode |= ENABLE_VIRTUAL_TERMINAL_INPUT;
	mode |= ENABLE_EXTENDED_FLAGS;
	mode |= ENABLE_WINDOW_INPUT;

	if(SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode) == 0) {
		tm_set_return(TM_COULDNT_INIT_TERM);
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
#ifndef _WIN32
	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask, SIGWINCH);

	sigprocmask(SIG_BLOCK, &mask, NULL);
	terminal->signal_fd = signalfd(-1, &mask, 0);

	if(terminal->signal_fd == -1) {
		tm_set_return(TM_COULDNT_INIT_TERM);
		return TM_ERROR;
	}
#endif

	char init[] = "\x1b[?1049h\x1b[2J\x1b[H\x1b[0m";

	write(fileno(stdout), init, strlen(init));
#ifdef _WIN32
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
#endif
	return 0;
}

int terminal_free() {
	char exit[] = "\x1b[0m\x1b(B\x1b[?25h\x1b[?1049l\x1b[?1003l\x1b[?1006l";

	write(fileno(stdout), exit, strlen(exit));
#ifdef _WIN32
	if(SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), og_output_mode) == 0) {
		tm_set_return(TM_COULDNT_INIT_TERM);
		return TM_ERROR;
	}

	if(SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), og_input_mode) == 0) {
		tm_set_return(TM_COULDNT_INIT_TERM);
		return TM_ERROR;
	}
#else
	tcsetattr(fileno(stdin), TCSANOW, &og_term);
	tcsetattr(fileno(stdout), TCSANOW, &og_term);

	close(terminal->signal_fd);
#endif
	free(terminal->buffer);
	free(terminal->output);
	free(terminal);

	terminal = NULL;

	return 0;
}
