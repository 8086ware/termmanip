#include "termmanip.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>

void tm_exit() {
	tm_win_free(default_win);
	write(fileno(stdout), TM_ESC_LEAVE_ALT_SCREEN, strlen(TM_ESC_ENTER_ALT_SCREEN));
	write(fileno(stdout), TM_ESC_ENABLE_CURSOR, strlen(TM_ESC_ENABLE_CURSOR));

	struct termios term;
	tcgetattr(fileno(stdin), &term);

	term.c_lflag |= ECHO;
	term.c_lflag |= ICANON;

	tcsetattr(fileno(stdin), TCSANOW, &term);
}
