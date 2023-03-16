#include <signal.h>
#include "termmanip.h"
#include <stdlib.h>

void signal_handle(int sig) {
	if(sig == SIGWINCH) {
		int scr_x, scr_y;
		tm_get_scrsize(&scr_x, &scr_y);
		tm_win_modify(default_win, 0, 0, scr_x, scr_y);
		tm_update();
	}

	else {
		tm_exit();
		exit(sig);
	}
}
