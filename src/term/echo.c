#include "termmanip.h"
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#endif

void tm_echo(int state) {
#ifdef _WIN32
	DWORD console_mode = 0;
	GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &console_mode);

	console_mode &= ~ENABLE_ECHO_INPUT;

	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), console_mode);
#else
	struct termios term;
	tcgetattr(fileno(stdin), &term);

	if(state <= 0) {
		term.c_lflag &= ~ECHO;
	}

	else if(state > 0) {	
		term.c_lflag |= ECHO;
	}

	tcsetattr(fileno(stdin), TCSANOW, &term);
#endif
}
