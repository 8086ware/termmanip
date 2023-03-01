#include "termmanip.h"
#include "append_win.h"

int tm_win_border(Tm_window* win) {
	int columns, rows;

	int cur_x = win->cursor_x, cur_y = win->cursor_y;

	tm_get_winsize(win, &columns, &rows);

	for(int y = 0; y < rows; y++) {
		for(int x = 0; x < columns; x++) {
			if((x == 0 && y == 0) || (x == columns - 1 && y == 0) || (x == 0 && y == rows - 1) || (x == columns - 1 && y == rows - 1)) {
				tm_win_cursor(win, x, y);
				append_win(win, "+");
			}

			else if(x == 0 || x == columns - 1) {
				tm_win_cursor(win, x, y);
				append_win(win, "|");
			}

			else if(y == 0 || y == rows - 1) {
				tm_win_cursor(win, x, y);
				append_win(win, "-");
			}
		}
	}

	tm_win_cursor(win, cur_x, cur_y);

	return 0;
}
