#include "termmanip.h"
#include <string.h>
#include <stdlib.h>
#include "error.h"

Tm_window* tm_win_button(Tm_window* win, int x, int y, int columns, int rows, char* text) {
	Tm_window* button = tm_window(x, y, columns, rows);

	tm_win_parent(win, button, TM_CHILD_BUTTON);
	
	tm_win_border(button);

	tm_win_cursor(button, columns / 2 - strlen(text) / 2, rows / 2);

	tm_win_print(button, text);

	return button;
}

Tm_window* tm_win_button_select(Tm_window* win) {
	uint16_t flags = tm_win_get_flags(win);
	
	tm_win_flags(win, TM_FLAG_INPUTBLOCK | TM_FLAG_RAW, 1);
	tm_win_flags(win, TM_FLAG_ECHO, 0);

	Tm_window** button_children = NULL;

	int button_children_amount = 0;

	for(int i = 0; i < win->children_amount; i++) {
		if(win->children[i]->child_type == TM_CHILD_BUTTON) {
			button_children = realloc(button_children, (button_children_amount + 1) * sizeof(Tm_window*));

			if(button_children == NULL) {
				tm_set_error(TM_OUT_OF_MEM);
				return NULL;
			}

			button_children[button_children_amount] = win->children[i];
			
			button_children_amount++;
		}
	}

	if(button_children_amount == 0) {
		return NULL;
	}

	int option = 0;
	char c = 0;

	Tm_char original_background = tm_win_get_background(win);

	while(1) {
		if(c == 'd') {
			option++;
		}

		else if(c == 'a') {
			option--;
		}

		else if(c == '\n' || c == '\r') {
			free(button_children);
			tm_win_flags(win, TM_FLAG_ALL, 0);
			tm_win_flags(win, flags, 1);
			return win->children[option];
		}

		if(option >= button_children_amount) {
			option = 0;
		}

		else if(option < 0) {
			option = button_children_amount - 1;
		}

		for(int i = 0; i < button_children_amount; i++) {
			if(i == option) {
				tm_win_background(button_children[i], original_background.disp, TM_ATTRIB_HIGHLIGHT);
			}

			else {
				tm_win_background(button_children[i], original_background.disp, original_background.attrib);
			}
		}

		c = tm_win_input_ch(win);
	}

}
