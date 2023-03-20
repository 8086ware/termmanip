#include "termmanip.h"
#include <unistd.h>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

void tm_win_update(Tm_window* win) {
#ifdef _WIN32
	DWORD bytes_written = 0;
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), win->contents, win->content_len, &bytes_written, NULL);
#else
	write(fileno(stdout), win->contents, win->content_len);
#endif
	tm_win_memclear(win);

	for(int i = 0; i < win->children_amount; i++) {
		tm_win_update(win->children[i]);
	}

}
