#include "termmanip.h"
#ifndef _WIN32
#include <sys/ioctl.h>
#else
#include <windows.h>
#endif

void tm_get_scrsize(int* x, int* y) {
#ifndef _WIN32
	struct winsize ws;

	ioctl(0, TIOCGWINSZ, &ws);

	*x = ws.ws_col;
	*y = ws.ws_row;
#else
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	*x = csbi.dwSize.X;
	*y = csbi.dwSize.Y;
#endif
}

void tm_set_scrsize(int x, int y) {
#ifndef _WIN32
	struct winsize ws;

	ws.ws_col = x;
	ws.ws_row = y;

	ioctl(1, TIOCSWINSZ, &ws);
#else
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	csbi.dwSize.X = x;
	csbi.dwSize.Y = y;

	COORD coord = {x,y};
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#endif
}
