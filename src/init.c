#include "termmanip.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "exit_log.h"
#include "append_output.h"
#include "signal_handler.h"
#include <signal.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

Tm_screen* screen = NULL;
struct termios og_term;

void tm_init() {
#ifdef _WIN32
	DWORD mode = 0;

	if(GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &mode) == 0) {
		exit_log("tm_init", "GetConsoleMode", 1);
	}

	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	if(SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), mode) == 0) {
		exit_log("tm_init", "SetConsoleMode", 1);
	}

	if(GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode) == 0) {
		exit_log("tm_init", "GetConsoleMode", 2);
	}

	mode &= ~ENABLE_ECHO_INPUT;
	mode &= ~ENABLE_LINE_INPUT;

	if(SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode) == 0) {
		exit_log("tm_init", "SetConsoleMode", 2);
	}
#else 
	struct termios term;
	tcgetattr(fileno(stdin), &term);
	og_term = term;
	
	cfmakeraw(&term);

	tcsetattr(fileno(stdin), TCSANOW, &term);
	tcsetattr(fileno(stdout), TCSANOW, &term);
#endif
	signal(SIGINT, signal_handle);
	signal(SIGTERM, signal_handle);
#ifdef _WIN32
#else
	signal(SIGWINCH, signal_handle);	
#endif	
	int scr_columns = 0, scr_rows = 0;

	tm_get_scrsize(&scr_columns, &scr_rows);

	screen = malloc(sizeof(Tm_screen));

	if(screen == NULL) {
		exit_log("tm_init", "malloc", 1);
	}

	screen->columns = scr_columns;
	screen->rows = scr_rows;

	screen->cursor_x = 0;
	screen->cursor_y = 0;

	screen->output = NULL;
	screen->output_len = 0;

	screen->attrib = TM_ATTRIB_RESET;

	screen->flags = 0;
	
	screen->buffer = malloc(sizeof(Tm_char) * screen->columns * screen->rows);
	screen->physical_buffer = malloc(sizeof(Tm_char) * screen->columns * screen->rows);

	if(screen->buffer == NULL || screen->physical_buffer == NULL) {
		exit_log("tm_init", "malloc", 2);
	}	

	for(int i = 0; i < screen->columns * screen->rows; i++) {
		screen->buffer[i].disp = ' ';
		screen->buffer[i].attrib = TM_ATTRIB_RESET;
		screen->physical_buffer[i].disp = ' ';
		screen->physical_buffer[i].attrib = TM_ATTRIB_RESET;
	}

	default_win = tm_window(0, 0, scr_columns, scr_rows);

	char init[] = "\x1b[?1049h\x1b[2J\x1b[H";

	write(fileno(stdout), init, strlen(init));
}

