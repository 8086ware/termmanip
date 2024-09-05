#include "termmanip.h"
#include <stdlib.h>

int main(void) {
	int scr_x, scr_y;
	Tm_terminal* terminal = tm_terminal();
	tm_get_termsize(&scr_x, &scr_y);
	Tm_window* win = tm_window(terminal, "window", 0, 0, scr_x, scr_y, NULL, TM_CHILD_NONE);
	
	tm_set_title("Termmanip Test");
	tm_win_flags(win, TM_FLAG_ECHO | TM_FLAG_CURSOR_VISIBLE, 0);
	tm_win_flags(win, TM_FLAG_TERMINAL_INPUT, 1);
	tm_win_input_timeout(win, 0);

	while(1) {
		tm_win_attrib(win, TM_ATTRIB_BG_MAGENTA, 1);
		tm_win_border(win);
		tm_win_cursor(win, 1, 0);
		tm_win_print(win, "Termmanip Color Test");
		tm_win_attrib(win, TM_ATTRIB_BG_MAGENTA, 0);

		int color = rand() % 15;

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

		tm_get_termsize(&scr_x, &scr_y);
		
		tm_win_fill(win, rand() % scr_x, rand() % scr_y, rand() % scr_x, rand() % scr_y, ' ', color);

		Tm_input t = tm_win_input(win);
		if(t.terminal_resized) {
			tm_get_termsize(&scr_x, &scr_y);
			tm_win_modify(win, 0, 0, scr_x, scr_y, 1);
		}

		else if(t.key == TM_KEY_Q) {
			break;
		}
	}

	tm_win_free(win);
	tm_terminal_free(terminal);
}
