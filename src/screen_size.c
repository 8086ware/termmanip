#include "termmanip.h"
#include <sys/ioctl.h>

void tmgscrsize(int* x, int* y) {
	struct winsize ws;

	ioctl(1, TIOCGWNSZ, &ws);

	*x = ws.ws_col;
	*y = ws.ws_row;
}

void tmsscrsize(int x, int y) {
	struct winsize ws;

	ws.ws_col = x;
	ws.ws_row = y;

	ioctl(1, TIOCSWNSZ, &ws);
}
