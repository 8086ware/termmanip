#include <termmanip.h>
#include <stdlib.h>

int main(void) {
	Tm_terminal* terminal = tm_terminal();

	if (terminal == NULL) {
		return 1;
	}

	int term_cols, term_rows;
	tm_get_termsize(&term_cols, &term_rows);

	Tm_window* win = tm_window(terminal, "test", 0, 0, term_cols, term_rows, NULL, TM_WIN_NONE, 0);

	if (win == NULL) {
		return 1;
	}

	tm_win_flags(win, TM_FLAG_WINDOW_SELECT | TM_FLAG_MOUSE_INPUT, 1);
	tm_win_input_timeout(win, 0);
	for (int i = 0; i < 500; i++) {
		tm_window(terminal, "test", rand() % term_cols, rand() % term_rows, 20, 5, win, TM_WIN_DIALOG, 2, "yes", "no");
		tm_win_input(win);
	}

	tm_win_free(win);
	tm_terminal_free(terminal);
}
