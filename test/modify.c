#include <termmanip.h>
#include <stdlib.h>

int main(void) {
	Tm_terminal* terminal = tm_terminal();

	int term_cols, term_rows;
	tm_get_termsize(&term_cols, &term_rows);

	Tm_window* win = tm_window(terminal, "test", 0, 0, term_cols, term_rows, NULL, TM_WIN_NONE, 0);

	tm_win_flags(win, TM_FLAG_SCROLL, 1);

	for(int i = 0; i < 1000; i++) {
		tm_win_print(win, "%c", rand() % 48 + 48);
		tm_win_update(win);
	}

	tm_win_flags(win, TM_FLAG_BORDER, 1);
	for(int i = 0; i < 1000; i++) {
		tm_win_modify(win, rand() % (term_cols - 1), rand() % (term_rows - 1), rand() % (term_cols - 1), rand() % (term_rows - 1), 0);
		tm_win_cursor(win, rand() % tm_win_get_buffer_columns(win) - 1, rand() % tm_win_get_buffer_rows(win) - 1);
		tm_win_print(win, "Hello World");
		tm_win_update(win);
	}

	tm_win_free(win);
	tm_terminal_free(terminal);
}
