#include "termmanip.h"
#include "append_win.h"
#include <stdio.h>
#include <string.h>

void tm_win_attrib(Tm_window* win, int attrib) {
	char buffer[32];

	sprintf(buffer, "\x1b[%dm", attrib);

	append_win_str(win, buffer, strlen(buffer));
}
