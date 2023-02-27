#include "termmanip.h"
#include "append_win.h"
#include <stdio.h>
#include <string.h>

void tm_win_attrib(Tm_window* win, int attrib) {
	append_win(win, "\x1b[%dm", attrib);
}
