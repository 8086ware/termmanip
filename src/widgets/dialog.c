#include "termmanip.h"
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "error.h"

int tm_win_dialog(Tm_window* win, int x, int y, int columns, int rows, uint16_t flags, char* title, char* message, const int option_amount, ...) {
	if(option_amount == 0) {
		tm_set_error(TM_DIALOG_NO_OPTIONS);
		return TM_ERROR;
	}

	int scr_x = 0, scr_y = 0;
	tm_get_scrsize(&scr_x, &scr_y);

	Tm_window* dialog = tm_window(x, y, columns, rows);

	tm_win_parent(win, dialog, TM_CHILD_NORMAL);

	tm_win_flags(dialog, TM_FLAG_ALL, 0);
	tm_win_flags(dialog, flags, 1);

	tm_win_border(dialog);

	tm_win_cursor(dialog, columns / 2 - ((strlen(title) / 2) + 2), 0);
	
	tm_win_attrib(dialog, TM_ATTRIB_ALTERNATE, 1);
	tm_win_print(dialog, "u");
	tm_win_attrib(dialog, TM_ATTRIB_ALTERNATE, 0);
	tm_win_print(dialog, title);
	tm_win_attrib(dialog, TM_ATTRIB_ALTERNATE, 1);
	tm_win_print(dialog, "t");
	tm_win_attrib(dialog, TM_ATTRIB_ALTERNATE, 0);

	tm_win_cursor(dialog, columns / 2 - strlen(message) / 2, 1);

	tm_win_print(dialog, message);

	va_list option_args;

	va_start(option_args, option_amount);

	int option_x = 2;
	int option_y = dialog->rows / 2;

	int option_columns = (columns - option_amount - 3) / option_amount;
 	int option_rows = rows / 3;

	Tm_window** buttons = malloc(sizeof(Tm_window*) * option_amount);

	for(int i = 0; i < option_amount; i++) {
		char* button_text = va_arg(option_args, char*);
		buttons[i] = tm_win_button(dialog, option_x, option_y, option_columns, option_rows, button_text);
		option_x += option_columns + 1;
	}

	tm_win_update(dialog);
	Tm_window* button_selected = tm_win_button_select(dialog);

	tm_win_clear(dialog);

	tm_win_update(dialog);

	for(int i = 0; i < option_amount; i++) {
		if(button_selected == buttons[i]) {
			for(int i = 0; i < option_amount; i++) {
				tm_win_free(buttons[i]);
			}

			tm_win_free(dialog);
			free(buttons);
			return i;
		}
	}

	return 0;
}
