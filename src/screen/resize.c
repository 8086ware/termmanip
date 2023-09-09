#include "screen.h"
#include "termmanip.h"
#include <stdlib.h>
#include "error.h"

int screen_resize() {
	int scr_x, scr_y;
	tm_get_scrsize(&scr_x, &scr_y);
	tm_win_modify(default_win, 0, 0, scr_x, scr_y);
	tm_win_clear(default_win);

	screen->buffer = realloc(screen->buffer, sizeof(Tm_char) * scr_x * scr_y);

	if(screen->buffer == NULL) {
		tm_set_error(TM_OUT_OF_MEM);
		return TM_ERROR;
	}

	screen->columns = scr_x;
	screen->rows = scr_y;

	return 0;
}
