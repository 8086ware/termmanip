#include "termmanip.h"
#include "terminal.h"

void update_terminal_flags(Tm_window* win) {
	Tm_window* parent = win->parent;

	int parent_x = 0;
	int parent_y = 0;

	while (parent != NULL) {
		parent_x += tm_win_get_pos_x(parent);
		parent_y += tm_win_get_pos_y(parent);

		parent = parent->parent;
	}

	if (win->flags & TM_FLAG_CURSOR_VISIBLE && (win->terminal->flags & TM_FLAG_CURSOR_VISIBLE) == 0) {
		terminal_append_output(win->terminal, "\x1b[?25h");
	}

	else if ((win->flags & TM_FLAG_CURSOR_VISIBLE) == 0 && win->terminal->flags & TM_FLAG_CURSOR_VISIBLE) {
		terminal_append_output(win->terminal, "\x1b[?25l");
	}

	if (win->flags & TM_FLAG_MOUSE_INPUT && (win->terminal->flags & TM_FLAG_MOUSE_INPUT) == 0) {
		terminal_append_output(win->terminal, "\x1b[?1003h\x1b[?1006h");
	}

	else if ((win->flags & TM_FLAG_MOUSE_INPUT) == 0 && win->terminal->flags & TM_FLAG_MOUSE_INPUT) {
		terminal_append_output(win->terminal, "\x1b[?1003l\x1b[?1006l");
	}

	if (win->flags & TM_FLAG_SHADOW) {
		for (int y = 1; y < tm_win_get_rows(win); y++) {
			Tm_char ch;
			ch.attrib = TM_ATTRIB_BG_BLACK | TM_ATTRIB_FG_BRIGHTBLACK;
			ch.disp = win->terminal->buffer[(y + tm_win_get_pos_y(win)) * win->terminal->columns + (tm_win_get_columns(win) + tm_win_get_pos_x(win))].disp;

			terminal_write(win->terminal, tm_win_get_pos_x(win) + tm_win_get_columns(win) + parent_x, tm_win_get_pos_y(win) + y + parent_y, ch.disp, ch.attrib);
		}

		for (int x = 1; x < tm_win_get_columns(win) + 1; x++) {
			Tm_char ch;
			ch.attrib = TM_ATTRIB_BG_BLACK | TM_ATTRIB_FG_BRIGHTBLACK;
			ch.disp = win->terminal->buffer[(tm_win_get_rows(win) + tm_win_get_pos_y(win)) * win->terminal->columns + (x + tm_win_get_pos_x(win))].disp;

			terminal_write(win->terminal, tm_win_get_pos_x(win) + x + parent_x, tm_win_get_pos_y(win) + tm_win_get_rows(win) + parent_y, ch.disp, ch.attrib);
		}
	}

	if (win->flags & TM_FLAG_BORDER) {
		for (int i = -1; i < win->columns + 1; i++) {
			terminal_write(win->terminal, parent_x + win->position_x + i, parent_y + win->position_y - 1, '\x71', win->background_tm_char.attrib | TM_ATTRIB_ALTERNATE);
		}

		for (int i = -1; i < win->columns + 1; i++) {
			terminal_write(win->terminal, parent_x + win->position_x + i, parent_y + win->position_y + win->rows, '\x71', win->background_tm_char.attrib | TM_ATTRIB_ALTERNATE);
		}

		for (int i = -1; i < win->rows + 1; i++) {
			terminal_write(win->terminal, parent_x + win->position_x - 1, parent_y + win->position_y + i, '\x78', win->background_tm_char.attrib | TM_ATTRIB_ALTERNATE);
		}

		for (int i = -1; i < win->rows + 1; i++) {
			terminal_write(win->terminal, parent_x + win->position_x + win->columns, parent_y + win->position_y + i, '\x78', win->background_tm_char.attrib | TM_ATTRIB_ALTERNATE);
		}

		terminal_write(win->terminal, parent_x + win->position_x - 1, parent_y + win->position_y - 1, '\x6c', win->background_tm_char.attrib | TM_ATTRIB_ALTERNATE);
		terminal_write(win->terminal, parent_x + win->position_x + win->columns, parent_y + win->position_y - 1, '\x6b', win->background_tm_char.attrib | TM_ATTRIB_ALTERNATE);
		terminal_write(win->terminal, parent_x + win->position_x - 1, parent_y + win->position_y + win->rows, '\x6d', win->background_tm_char.attrib | TM_ATTRIB_ALTERNATE);
		terminal_write(win->terminal, parent_x + win->position_x + win->columns, parent_y + win->position_y + win->rows, '\x6a', win->background_tm_char.attrib | TM_ATTRIB_ALTERNATE);
	}

	else if ((win->flags & TM_FLAG_BORDER) == 0) {
		for (int i = -1; i < win->columns + 1; i++) {
			terminal_write(win->terminal, parent_x + win->position_x + i, parent_y + win->position_y - 1, ' ', 0);
		}

		for (int i = -1; i < win->columns + 1; i++) {
			terminal_write(win->terminal, parent_x + win->position_x + i, parent_y + win->position_y + win->rows, ' ', 0);
		}

		for (int i = -1; i < win->rows + 1; i++) {
			terminal_write(win->terminal, parent_x + win->position_x - 1, parent_y + win->position_y + i, ' ', 0);
		}

		for (int i = -1; i < win->rows + 1; i++) {
			terminal_write(win->terminal, parent_x + win->position_x + win->columns, parent_y + win->position_y + i, ' ', 0);
		}
	}

	win->terminal->flags = win->flags;
}