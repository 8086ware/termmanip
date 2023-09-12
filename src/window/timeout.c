#include "termmanip.h"

void tm_win_input_timeout(Tm_window* win, int timeout) {
	win->input_timeout = timeout;
}
