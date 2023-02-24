#include <termios.h>
#include "termmanip.h"
#include <stdio.h>

void tm_rawinput(int state) {	
	struct termios term;
	tcgetattr(fileno(stdin), &term);

	if(state > 0) {
		term.c_lflag &= ~ICANON;
	}

	else if(state <= 0) {	
		term.c_lflag |= ICANON;
	}

	tcsetattr(fileno(stdin), TCSANOW, &term);
}
