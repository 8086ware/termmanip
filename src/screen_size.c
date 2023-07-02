#include "termmanip.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#endif

void tm_get_scrsize(int* x, int* y) {
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	*x = csbi.srWindow.Right + 1;
	*y = csbi.srWindow.Bottom + 1;
#else
	struct winsize ws;

	ioctl(0, TIOCGWINSZ, &ws);

	*x = ws.ws_col;
	*y = ws.ws_row;
#endif
}
