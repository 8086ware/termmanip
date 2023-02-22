#include "termmanip.h"

int main(void) {
	tm_init();

	Tm_window* test = tm_window(5, 5, 20, 10);
	
	tm_win_parent(default_win, test);

	tm_win_border(default_win);
	tm_win_border(test);

	tm_update();

	getchar();

	tm_exit();
}
