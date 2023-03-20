#include "termmanip.h"
#include "exit_log.h"
#include <stdlib.h>

int tm_win_parent(Tm_window* parent, Tm_window* child, int type) {
	tm_win_memclear(child);

	child->parent = parent;
	child->child_type = type;
	
	parent->children = realloc(parent->children, (parent->children_amount + 1) * sizeof(Tm_window*));

	if(parent->children == NULL) {
		exit_log("tm_win_parent", "realloc", 1);
	}

	parent->children[parent->children_amount] = child;
	
	parent->children_amount++;

	tm_win_cursor(child, 0, 0);
	tm_win_attrib(child, TM_ATTRIB_RESET);

	tm_win_clear(child);

	return 0;
}
