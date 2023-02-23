#include "termmanip.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(void) {
	tm_init();

	Tm_window* win = tm_window(10, 10, 10, 10);

	tm_win_background(win, TM_ATTRIB_BG_WHITE);	
	tm_win_attrib(win, TM_ATTRIB_FG_BLACK);
	tm_win_print_str(win, "Hello world!\n");
	tm_win_update(win);
	getchar();
	tm_exit();
}
