#include "termmanip.h"
#include <time.h>

int main(void) {
	tm_init();

	for(int i = 0; i < 100000; i++) {
		tm_cursor(0, 0);
		tm_print("Loading... %d", i);
		tm_update();
	}

	tm_cursor(10, 10);
	tm_print("Done!");
	tm_update();
	sleep(2);

	tm_clear();
	tm_print("Hello World");
	tm_clear();
	tm_print("Hello... World?");
	tm_fill(10, 10, 20, 20, 't', TM_ATTRIB_BG_BLUE);
	tm_update();
	char buffer[1024];
	Tm_window* win = tm_window(40, 20, 10, 10);
	tm_win_border(win);
	tm_win_input_str(win, buffer, 1024);

	tm_attrib(TM_ATTRIB_BG_RED);
	int scr_x, scr_y;
	tm_get_scrsize(&scr_x, &scr_y);

	int i = 0;

	while(i != 1000) {
		tm_cursor(rand() % scr_x, rand() % scr_y);
		tm_print("ERROR");
		tm_update();
		usleep(1000);
		i++;
	}

	tm_attrib(TM_ATTRIB_BG_YELLOW);
	tm_clear();
	tm_update();

	sleep(3);

	tm_print("Welcome to termmanip. Enjoy your tui!");
	tm_update();

	tm_button(10, 10, 10, 10, "Of course");
	tm_button(0, 5, 10, 10, "Heck No");

	tm_button_select();
	tm_input_ch();
	tm_exit();
}
