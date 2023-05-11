#ifndef _WIN32
#include "termmanip.h"
#include <termios.h>
#include <stdio.h>

void terminal_inputblock(int state) {
	struct termios term;
	tcgetattr(fileno(stdin), &term);

	if(state <= 0) {
		term.c_cc[VMIN] = 0;
	}

	else if(state > 0) {	
		term.c_cc[VMIN] = 1;
	}

	tcsetattr(fileno(stdin), TCSANOW, &term);
}
#endif
