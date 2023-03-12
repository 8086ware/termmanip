#include "termmanip.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#endif
#include <stdio.h>

int tm_inputblock(int state) {
#ifdef _WIN32

#else
	struct termios term;
	tcgetattr(fileno(stdin), &term);

	static int prev_state = 0;

	if(term.c_cc[VMIN] == 0) {
		prev_state = 0;
	}

	else {
		prev_state = 1;
	}
	
	term.c_cc[VTIME] = 0;

	if(state <= 0) {
		term.c_cc[VMIN] = 0;
	}

	else if(state > 0) {	
		term.c_cc[VMIN] = 1;
	}

	tcsetattr(fileno(stdin), TCSANOW, &term);

	return prev_state;
#endif
}
