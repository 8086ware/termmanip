#include "termmanip.h"
#include "exit_log.h"
#include <string.h>
#include <stdlib.h>

Tm_window* tm_win_button(Tm_window* win, int x, int y, int columns, int rows, char* text) {
	Tm_window* button = tm_window(x, y, columns, rows);

	tm_win_parent(win, button, TM_CHILD_BUTTON);
	
	tm_win_border(button);

	tm_win_cursor(button, columns / 2 - strlen(text) / 2, rows / 2);

	tm_win_print(button, text);

	return button;
}

Tm_window* tm_win_button_select(Tm_window* win) {
	unsigned char flags = win->flags;

	tm_win_echo(win, 0);
	tm_win_raw(win, 1);
	int prev_state = tm_inputblock(1);

	Tm_window** button_children = NULL;
	int button_children_amount = 0;

	for(int i = 0; i < win->children_amount; i++) {
		if(win->children[i]->child_type == TM_CHILD_BUTTON) {
			button_children = realloc(button_children, (button_children_amount + 1) * sizeof(Tm_window*));

			if(button_children == NULL) {
				exit_log("tm_win_button_select", "realloc", 1);
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

	while(1) {

		if(c == 'd') {
			option++;
		}

		else if(c == 'a') {
			option--;
		}

		else if(c == '\n' || c == '\r') {
			free(button_children);
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
				tm_win_background(button_children[i], TM_ATTRIB_HIGHLIGHT);
			}

			else {
				tm_win_background(button_children[i], TM_ATTRIB_RESET);
			}
		}

		c = tm_win_input_ch(win);
	}

	tm_inputblock(prev_state);
	win->flags = flags;
}
