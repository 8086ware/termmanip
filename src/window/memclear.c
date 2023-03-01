#include "termmanip.h"
#include <stdlib.h>

void tm_win_memclear(Tm_window* win) {
	if(win->contents == NULL || win == NULL) {
		return;
	}

	free(win->contents);
	win->contents = NULL;
	win->content_len = 0;
}
