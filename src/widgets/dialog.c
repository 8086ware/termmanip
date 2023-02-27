#include "termmanip.h"
#include <string.h>
#include <stdarg.h>

int tm_win_dialog(Tm_window* win, int x, int y, int columns, int rows, char* message, const int option_amount, ...) {
	va_list option_args;

	Tm_window* dialog = tm_window(x, y, columns, rows);
	tm_win_parent(win, dialog, TM_CHILD_NORMAL);
	tm_win_border(dialog);
	tm_win_cursor(dialog, columns / 2 - strlen(message) / 2, rows / 4);
	tm_win_print(dialog, message);

	Tm_window* buttons[option_amount];

	va_start(option_args, option_amount);
	char* options[option_amount];
	columns--;
	rows--;
	x++;
	y++;

	int option_columns = columns / option_amount - 2;
	int option_rows = rows / 4;
	int option_x = x + 1;
	int option_y = (rows - rows / 4) - 1;

	for(int i = 0; i < option_amount; i++) {
		options[i] = va_arg(option_args, char*);
		buttons[i] = tm_window(option_x, option_y, option_columns, option_rows);
		tm_win_border(buttons[i]);
		tm_win_cursor(buttons[i], option_columns / 2 - strlen(options[i]) / 2, 1);
		tm_win_print(buttons[i], options[i]);
		tm_win_parent(dialog, buttons[i], TM_CHILD_BUTTON);
		option_x += columns / option_amount;
	}

	va_end(option_args);
	tm_win_update(dialog);

	Tm_window* selection = tm_win_button_select(dialog);

	tm_win_clear(win);
	tm_win_update(win);
	for(int i = 0; i < option_amount; i++) {
		if(selection == buttons[i]) {
			return i;
		}
	}

	return TM_DIALOG_NO_SELECT;
}
