#include "termmanip.h"

int main(void) {
	tm_init();
	tm_background(TM_ATTRIB_BG_BLUE);
	tm_attrib(TM_ATTRIB_FG_RED);
	tm_cursor(1, 1);
	tm_print("Hello World!\n%d%c%f", 10, 'c', 10.1);
	tm_update();
	tm_input_ch();

	int i = tm_dialog(0, 0, 50, 30, "Hello World! Dialog test", 2, "Yes", "No");

	if(i == 0) {
		tm_print("Yes pressed\n");
	}

	else {
		tm_print("No pressed\n");
	}

	tm_update();

	tm_input_ch();
	tm_exit();
}
