#include "termmanip.h"
#include "terminal.h"
#include "term.h"

Tm_terminal* terminal = NULL;

int tm_init() {
	if(terminal_init() == TM_ERROR) {
		return TM_ERROR;
	}

	int scr_columns = 0, scr_rows = 0;
	tm_get_scrsize(&scr_columns, &scr_rows);

	default_win = tm_window(0, 0, scr_columns, scr_rows);

	if(default_win == NULL) {
		return TM_ERROR;
	}


	return 0;
}

