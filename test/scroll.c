#include <termmanip.h>
#include <stdlib.h>

int main(void) {
	Tm_terminal* terminal = tm_terminal();

	if(terminal == NULL) {
		return 1;
	}

	int term_cols, term_rows;
	tm_get_termsize(&term_cols, &term_rows);

	Tm_window* win = tm_window(terminal, "test", 0, 0, term_cols, term_rows, NULL, TM_WIN_NONE, 0);

	if(win == NULL) {
		return 1;
	}

	tm_win_flags(win, TM_FLAG_SCROLL, 1);

	for(int i = 0; i < 1000; i++) {
		tm_win_print(win, "%c", rand() % 48 + 48);
		tm_win_update(win);
	}

	for(int i = 0; i < 1000; i++) {
		tm_win_cursor(win, 250 - rand() % 500, 250 - rand() % 500);
		tm_win_print(win, "Test");
		tm_win_update(win);
	}

	tm_win_free(win);
	tm_terminal_free(terminal);
}
