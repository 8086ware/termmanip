#include "termmanip.h"
#include "exit_log.h"
#include <string.h>
#include <stdlib.h>

Tm_window* tm_win_button(Tm_window* win, int x, int y, int columns, int rows, char* text) {
	Tm_window* button = tm_window(x, y, columns, rows);

	tm_win_parent(win, button, TM_CHILD_BUTTON);
	
	tm_win_border(button);

	tm_win_cursor(button, columns / 2 - strlen(text) / 2, rows / 2);

	tm_win_print_str(button, text);

	return button;
}

Tm_window* tm_win_button_select(Tm_window* win) {
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

	while(1) {
		tm_win_update(win);

		char c = tm_input_ch();

		if(c == 'd') {
			option++;
		}

		else if(c == 'a') {
			option--;
		}

		else if(c == '\n') {
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
				tm_win_cursor(button_children[i], 0, 0);
			}
		}
	}
}