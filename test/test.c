#include "termmanip.h"

int main(void) {
	tm_init();
	tm_set_title("Termmanip Test");
	tm_dialog("Test", "Testing", 2, "Ok", "No");
	tm_flags(TM_FLAG_ECHO | TM_FLAG_CURSOR_VISIBLE, 0);
	tm_input_timeout(0);

	while(1) {
		tm_attrib(TM_ATTRIB_BG_MAGENTA, 1);
		tm_win_border(default_win);
		tm_cursor(1, 0);
		tm_print("Termmanip Color Test");
		tm_attrib(TM_ATTRIB_BG_MAGENTA, 0);

		uint32_t color = rand() % 15;

		switch(color) {
				case 0:
				color = TM_ATTRIB_BG_BLACK;
				break;
				case 1:
				color = TM_ATTRIB_BG_RED;
				break;
				case 2:
				color = TM_ATTRIB_BG_GREEN;
				break;
				case 3:
				color = TM_ATTRIB_BG_YELLOW;
				break;
				case 4:
				color = TM_ATTRIB_BG_BLUE;
				break;
				case 5:
				color = TM_ATTRIB_BG_MAGENTA;
				break;
				case 6:
				color = TM_ATTRIB_BG_CYAN;
				break;
				case 7:
				color = TM_ATTRIB_BG_WHITE;
				break;
				case 8:
				color = TM_ATTRIB_BG_BRIGHTBLACK;
				break;
				case 9:
				color = TM_ATTRIB_BG_BRIGHTRED;
				break;
				case 10:
				color = TM_ATTRIB_BG_BRIGHTGREEN;
				break;
				case 11:
				color = TM_ATTRIB_BG_BRIGHTYELLOW;
				break;
				case 12:
				color = TM_ATTRIB_BG_BRIGHTBLUE;
				break;
				case 13:
				color = TM_ATTRIB_BG_BRIGHTMAGENTA;
				break;
				case 14:
				color = TM_ATTRIB_BG_BRIGHTCYAN;
				break;
				case 15:
				color = TM_ATTRIB_BG_BRIGHTWHITE;
				break;
		}

		int scr_x, scr_y;
		tm_get_scrsize(&scr_x, &scr_y);
		
		tm_fill(rand() % scr_x, rand() % scr_y, rand() % scr_x, rand() % scr_y, ' ', color);

		if(tm_input().terminal_resized) {
			tm_get_scrsize(&scr_x, &scr_y);
			tm_win_modify(default_win, 0, 0, scr_x, scr_y);
		}
	}

	tm_exit();
}
