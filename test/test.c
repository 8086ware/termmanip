#include "termmanip.h"

int main(void) {
	tm_init();

	Tm_window* test = tm_window(5, 5, 20, 10);

	tm_win_print_str(test, "Ok buddy retard");

	tm_win_update(test);

	getchar();

	tm_exit();
}
