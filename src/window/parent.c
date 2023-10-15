#include "termmanip.h"
#include <stdlib.h>
#include "return.h"

int tm_win_parent(Tm_window* parent, Tm_window* child, int type) {
	child->parent = parent;
	child->child_type = type;
	
	parent->children = realloc(parent->children, (parent->children_amount + 1) * sizeof(Tm_window*));

	if(parent->children == NULL) {
		tm_set_return(TM_OUT_OF_MEM);
		return TM_ERROR;
	}

	parent->children[parent->children_amount] = child;
	
	parent->children_amount++;

	tm_win_background(child, parent->background_tm_char.disp, parent->background_tm_char.attrib);

	tm_win_flags(child, TM_FLAG_ALL, 0);
	tm_win_flags(child, parent->flags, 1);

	return 0;
}
