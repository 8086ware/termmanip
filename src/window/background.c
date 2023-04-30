#include "termmanip.h"
#include <stdlib.h>
#include <string.h>
#include "exit_log.h"

int tm_win_background(Tm_window* win, char ch, uint32_t attrib) {
	int ret = 0;

	win->background_tm_char.attrib = attrib;
	win->background_tm_char.disp = ch;

	tm_win_clear(win);

	return 0;
}
