#include "termmanip.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void tm_init() {
	write(fileno(stdout), TM_ESC_ENTER_ALT_SCREEN, strlen(TM_ESC_ENTER_ALT_SCREEN));
	write(fileno(stdout), "\x1b[2J", strlen("\x1b[2J"));
}

