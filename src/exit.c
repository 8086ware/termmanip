#include "termmanip.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void tm_exit() {
	write(fileno(stdout), TM_ESC_LEAVE_ALT_SCREEN, strlen(TM_ESC_ENTER_ALT_SCREEN));
}
