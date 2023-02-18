#ifndef TERMMANIP_H
#define TERMMANIP_H

#define TM_WIN_NULL 1
#define TM_WIN_INVALID_DIMENSIONS 2

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

void tm_get_scrsize(int* x, int* y);
void tm_set_scrsize(int x, int y);

#endif

