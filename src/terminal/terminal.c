#include "termmanip.h"
#include "terminal.h"
#include <stdlib.h>
#include "return.h"
#include <stdio.h>
#include <signal.h>
#include <string.h>

#ifndef _WIN32
#include <sys/signalfd.h>
#include <unistd.h>
#endif

Tm_terminal* tm_terminal() {
	int scr_columns, scr_rows;
	tm_get_termsize(&scr_columns, &scr_rows);
	Tm_terminal* terminal = malloc(sizeof(Tm_terminal));

	if(terminal == NULL) {
		return NULL;
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
	terminal->physical_buffer = malloc(sizeof(Tm_char) * terminal->columns * terminal->rows);

	if(terminal->buffer == NULL || terminal->physical_buffer == NULL) {
		tm_set_return(terminal, TM_OUT_OF_MEM);
		return NULL;
	}	

	for(int i = 0; i < terminal->columns * terminal->rows; i++) {
		terminal->buffer[i].disp = ' ';
		terminal->buffer[i].attrib = 0;
		terminal->physical_buffer[i].disp = ' ';
		terminal->physical_buffer[i].attrib = 0;
	}

#ifdef _WIN32
	DWORD mode = 0;

	if(GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &mode) == 0) {
		tm_set_return(terminal, TM_COULDNT_INIT_TERM);
		return NULL;
	}

	terminal->og_output_mode = mode;

	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	if(SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), mode) == 0) {
		tm_set_return(terminal, TM_COULDNT_INIT_TERM);
		return NULL;
	}

	if(GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode) == 0) {
		tm_set_return(terminal, TM_COULDNT_INIT_TERM);
		return NULL;
	}

	terminal->og_input_mode = mode;

	mode &= ~ENABLE_ECHO_INPUT;
	mode &= ~ENABLE_LINE_INPUT;

	mode |= ENABLE_VIRTUAL_TERMINAL_INPUT;
	mode |= ENABLE_EXTENDED_FLAGS;
	mode |= ENABLE_WINDOW_INPUT;

	if(SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode) == 0) {
		tm_set_return(terminal, TM_COULDNT_INIT_TERM);
		return NULL;
	}

#else 
	struct termios term;
	tcgetattr(fileno(stdin), &term);
	terminal->og_term = term;

	term.c_lflag &= ~ECHO;
	term.c_lflag &= ~ICANON;

	tcsetattr(fileno(stdin), TCSANOW, &term);
#endif
#ifndef _WIN32
	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask, SIGWINCH);

	sigprocmask(SIG_BLOCK, &mask, NULL);
	terminal->signal_fd = signalfd(-1, &mask, 0);

	if(terminal->signal_fd == -1) {
		tm_set_return(terminal, TM_COULDNT_INIT_TERM);
		return NULL;
	}
#endif

	char init[] = "\x1b[?1049h\x1b[2J\x1b[H\x1b[0m";

#ifdef _WIN32
	DWORD bytes_written = 0;
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), init, strlen(init), &bytes_written, NULL);
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
#else
	write(fileno(stdout), init, strlen(init));
#endif

	terminal->last_updated_window = NULL;
	return terminal;
}

int tm_terminal_free(Tm_terminal* terminal) {
	char exit[] = "\x1b[0m\x1b(B\x1b[?25h\x1b[?1049l\x1b[?1003l\x1b[?1006l";

#ifdef _WIN32
	DWORD bytes_written = 0;
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), exit, strlen(exit), &bytes_written, NULL);
	if(SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), terminal->og_output_mode) == 0) {
		tm_set_return(terminal, TM_COULDNT_INIT_TERM);
		return TM_ERROR;
	}

	if(SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), terminal->og_input_mode) == 0) {
		tm_set_return(terminal, TM_COULDNT_INIT_TERM);
		return TM_ERROR;
	}
#else
	write(fileno(stdout), exit, strlen(exit));

	tcsetattr(fileno(stdin), TCSANOW, &terminal->og_term);
	tcsetattr(fileno(stdout), TCSANOW, &terminal->og_term);

	close(terminal->signal_fd);
#endif
	free(terminal->buffer);
	free(terminal->output);
	free(terminal->physical_buffer);

	free(terminal);

	terminal = NULL;

	return 0;
}
