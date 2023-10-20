#include "termmanip.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "terminal.h"
#include "error.h"

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

int tm_exit() {
	if(tm_win_free(default_win) == TM_ERROR) {
		return TM_ERROR;	
	}

	if(terminal_free() == TM_ERROR) {
		return TM_ERROR;
	}

	return 0;
}
