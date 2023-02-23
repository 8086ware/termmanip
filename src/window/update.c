#include "termmanip.h"
#include <unistd.h>
#include <stdio.h>

void tm_win_update(Tm_window* win) {
	write(fileno(stdout), win->contents, win->content_len);

	if(win->children != NULL) {
		for(int i = 0; i < win->children_amount; i++) {
			tm_win_update(win->children[i]);
		}
	}


	tm_win_clear(win);
}
