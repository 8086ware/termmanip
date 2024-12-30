#include "termmanip.h"
#include <stdlib.h>
#include "return.h"

int tm_win_parent(Tm_window* parent, Tm_window* child) {
	child->parent = parent;
	
	parent->children = realloc(parent->children, (parent->children_amount + 1) * sizeof(Tm_window*));

	if(parent->children == NULL) {
		tm_set_return(parent->terminal, TM_OUT_OF_MEM);
		return TM_ERROR;
	}

	parent->children[parent->children_amount] = child;

	parent->children_amount++;

	return 0;
}
