#include <termmanip.h>

int main(void) {
	tm_init();

	Tm_window* test = tm_window(1, 1, 5, 5);
	
	tm_win_border(test);
	
	tm_win_update(test);
	getchar();

	tm_exit();
}
