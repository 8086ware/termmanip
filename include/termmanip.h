#ifndef TERMMANIP_H
#define TERMMANIP_H

#include <wchar.h>

typedef struct _Tm_window {
	int position_x, position_y, columns, rows;
	int cursor_x, cursor_y;

	struct _Tm_window* parent;
	struct _Tm_window** children;

	int children_amount;

	wchar_t* contents;
	int content_len;
} Tm_window;

#endif
