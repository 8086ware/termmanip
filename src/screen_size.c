#include "termmanip.h"
#include <sys/ioctl.h>

void tm_get_scrsize(int* x, int* y) {
	struct winsize ws;

	ioctl(1, TIOCGWINSZ, &ws);

	*x = ws.ws_col;
	*y = ws.ws_row;
}

void tm_set_scrsize(int x, int y) {
	struct winsize ws;

	ws.ws_col = x;
	ws.ws_row = y;

	ioctl(1, TIOCSWINSZ, &ws);
}
