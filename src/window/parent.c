#include "termmanip.h"
#include <stdlib.h>
#include "return.h"

int tm_win_parent(Tm_window* parent, Tm_window* child, enum Tm_child_type type) {
	child->parent = parent;
	child->child_type = type;

	switch(type) {
		case TM_CHILD_BUTTON:
			tm_win_cursor(child, child->columns / 2 - child->name_length / 2, child->rows / 2);
			tm_win_print(child, "%s", child->name);
			break;
		case TM_CHILD_TEXTBOX:
			tm_win_print(child, "%s", child->name);
			break;
		break;
	}
	
	parent->children = realloc(parent->children, (parent->children_amount + 1) * sizeof(Tm_window*));

	if(parent->children == NULL) {
		tm_set_return(parent->terminal, TM_OUT_OF_MEM);
		return TM_ERROR;
	}

	parent->children[parent->children_amount] = child;
	
	if(parent->children_amount == 0) {
		parent->selected_child_window = child;
	}

	parent->children_amount++;

	return 0;
}
