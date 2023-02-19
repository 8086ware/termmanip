#include "termmanip.h"
#include "exit_log.h"
#include <stdlib.h>

void tm_win_parent(Tm_window* parent, Tm_window* child) {
	child->parent = parent;
	
	parent->children = realloc(parent->children, (parent->children_amount + 1) * sizeof(Tm_window*));

	if(parent->children == NULL) {
		exit_log("tm_win_parent", "realloc", 1);
	}

	parent->children[parent->children_amount] = child;

	parent->children_amount++;
}
