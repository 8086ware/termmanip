#include "append_win.h"
#include "termmanip.h"
#include "exit_log.h"
#include <stdlib.h>
#include <string.h>

void append_win_str(Tm_window* win, char* data) {
	int len = strlen(data);
	win->contents = realloc(win->contents, win->content_len + len + 1);

	if(win->contents == NULL) {
		exit_log("append_win", "realloc", 1);
	}

	for(int i = 0; i < len; i++) {
		win->contents[win->content_len + i] = data[i];
	}

	win->content_len += len;
}

void append_win_ch(Tm_window* win, char data) {
	int len = 1;
	win->contents = realloc(win->contents, win->content_len + len + 1);

	if(win->contents == NULL) {
		exit_log("append_win", "realloc", 1);
	}

	for(int i = 0; i < len; i++) {
		win->contents[win->content_len + i] = data;
	}

	win->content_len += len;

}
