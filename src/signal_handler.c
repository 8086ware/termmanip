#include <signal.h>
#include "termmanip.h"
#include <stdlib.h>
#include "screen.h"

void signal_handle(int sig) {
#ifdef _WIN32
#else
	if(sig == SIGWINCH) {
		screen_resize();
		return;
	}
#endif
	tm_exit();
	exit(sig);
}
