#include <signal.h>
#include "termmanip.h"
#include <stdlib.h>
#include "terminal.h"

void signal_handle(int sig) {
	if(sig == SIGINT) {
		tm_exit();
		exit(sig);
	}
}
