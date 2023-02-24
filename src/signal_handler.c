#include <signal.h>
#include "termmanip.h"
#include <stdlib.h>

void signal_handle(int sig) {
	tm_exit();
	exit(sig);
}
