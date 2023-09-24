#include <signal.h>
#include "termmanip.h"
#include <stdlib.h>
#include "screen.h"

void signal_handle(int sig) {
	if(sig == SIGINT) {
		tm_exit();
		exit(sig);
	}

#ifndef _WIN32
	else if(sig == SIGWINCH) {
		screen_resize();
	}
#endif
}
