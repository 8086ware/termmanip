#include "termmanip.h"
#include "append_win.h"
#include <stdlib.h>
#include <string.h>
#include "exit_log.h"

int tm_win_background(Tm_window* win, int attrib) {
	int ret = 0;

	if((ret = tm_win_attrib(win, attrib)) == TM_ERROR) {
		return ret;
	}

	if((ret = tm_win_clear(win)) == TM_ERROR) {
		return ret;
	}

	if((ret = tm_win_cursor(win, 0, 0)) == TM_ERROR) {
		return ret;
	}

	return 0;
}
