#include <signal.h>
#include "termmanip.h"
#include <stdlib.h>
#include "pending_change.h"

void signal_handle(int sig) {
#ifdef _WIN32
#else
	if(sig == SIGWINCH) {
		int scr_x, scr_y;
		tm_free_pending_changes();
		tm_get_scrsize(&scr_x, &scr_y);
		tm_win_modify(default_win, 0, 0, scr_x, scr_y);
		tm_win_clear(default_win);
		return;
	}
#endif
	tm_exit();
	exit(sig);
}
