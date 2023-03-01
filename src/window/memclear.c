#include "termmanip.h"
#include <stdlib.h>

int tm_win_memclear(Tm_window* win) {
	if(win->contents == NULL || win == NULL) {
		return 0;
	}

	free(win->contents);
	win->contents = NULL;
	win->content_len = 0;

	return 0;
}
