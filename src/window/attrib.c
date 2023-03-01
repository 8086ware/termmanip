#include "termmanip.h"
#include "append_win.h"
#include <stdio.h>
#include <string.h>

int tm_win_attrib(Tm_window* win, int attrib) {
	return append_win(win, "\x1b[%dm", attrib);
}
