#include "termmanip.h"
#include <stdlib.h>

int tm_win_clear(Tm_window* win) {
	if(win->contents == NULL) {
		return TM_WIN_CONTENTS_NULL;
	}

	free(win->contents);
	win->contents = NULL;
	win->content_len = 0;

	return 1;
}
