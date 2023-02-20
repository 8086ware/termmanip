#include "termmanip.h"

int main(void) {
	tm_init();

	Tm_window* test = tm_window(5, 5, 20, 10);
	Tm_window* test_child = tm_window(5, 5, 3, 3);
	
	tm_win_parent(test, test_child);

	tm_win_border(test);
	tm_win_border(test_child);

	tm_win_update(test);

	getchar();

	tm_exit();
}
