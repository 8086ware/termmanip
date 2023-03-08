#include "termmanip.h"
#include <string.h>
#include <stdarg.h>

int tm_win_dialog(Tm_window* win, int x, int y, int columns, int rows, char* message, const int option_amount, ...) {
	Tm_window* dialog = tm_window(x, y, columns, rows);
	
	tm_win_parent(win, dialog, TM_CHILD_NORMAL);

	tm_win_border(dialog);

	tm_win_cursor(dialog, columns / 2 - strlen(message) / 2, rows / 2);

	tm_win_print(dialog, message);

	va_list option_args;

	va_start(option_args, option_amount);

	if(option_amount == 0) {
		tm_error_number = TM_DIALOG_NO_OPTIONS;
		return TM_ERROR;
	}

	int option_x = 0;
	int option_y = rows - 4;

	int option_columns = columns / option_amount;
	int option_rows = 3;

	Tm_window* buttons[option_amount];

	for(int i = 0; i < option_amount; i++) {

		char* button_text = va_arg(option_args, char*);
		buttons[i] = tm_win_button(dialog, option_x, option_y, option_columns, option_rows, button_text);
		option_x += option_columns;
	}

	tm_win_update(dialog);
	Tm_window* button_selected = tm_win_button_select(dialog);

	for(int i = 0; i < option_amount; i++) {
		if(button_selected == buttons[i]) {
			return i;
		}
	}

	return 0;
}
