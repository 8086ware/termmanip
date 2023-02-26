#include "append_win.h"
#include "termmanip.h"
#include "exit_log.h"
#include <stdlib.h>
#include <string.h>

void append_win_str(Tm_window* win, char* data, int size) {
	win->contents = realloc(win->contents, win->content_len + size);

	if(win->contents == NULL) {
		exit_log("append_win", "realloc", 1);
	}

	for(int i = 0; i < size; i++) {
		win->contents[win->content_len + i] = data[i];
	}

	win->content_len += size;
}

void append_win_ch(Tm_window* win, char data) {
	int size = 1;
	win->contents = realloc(win->contents, win->content_len + size);

	if(win->contents == NULL) {
		exit_log("append_win", "realloc", 1);
	}

	for(int i = 0; i < size; i++) {
		win->contents[win->content_len + i] = data;
	}

	win->content_len += size;
}
