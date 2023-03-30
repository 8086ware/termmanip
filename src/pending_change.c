#include "termmanip.h"
#include <stdlib.h>
#include "exit_log.h"

void tm_add_pending_change(Tm_char tm_char, int x, int y) {
	screen->pending_changes = realloc(screen->pending_changes, sizeof(Pending_Change) * (screen->pending_change_amount + 1));

	if(screen->pending_changes == NULL) {
		exit_log("tm_add_pending_change", "realloc", 1);
	}

	screen->pending_change_amount++;

	screen->pending_changes[screen->pending_change_amount - 1].x = x;
	screen->pending_changes[screen->pending_change_amount - 1].y = y;

	screen->pending_changes[screen->pending_change_amount - 1].tm_char = tm_char;
}

void tm_free_pending_changes() {
	free(screen->pending_changes);
	screen->pending_changes = NULL;

	screen->pending_change_amount = 0;
}
