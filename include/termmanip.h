#ifndef TERMMANIP_H
#define TERMMANIP_H

#define TM_WIN_NULL 1
#define TM_WIN_INVALID_DIMENSIONS 2
#define TM_INVALID_CURSOR 3
#define TM_WIN_CONTENTS_NULL 4

#define TM_ESC_ENTER_ALT_SCREEN "\x1b[?1049h"
#define TM_ESC_LEAVE_ALT_SCREEN "\x1b[?1049l"

#include <stddef.h>

typedef struct _Tm_window {
	int position_x, position_y, columns, rows;
	int cursor_x, cursor_y;

	struct _Tm_window* parent;
	struct _Tm_window** children;

	int children_amount;

	char* contents;
	int content_len;
} Tm_window;

extern Tm_window* default_win;

Tm_window* tm_window(int x, int y, int columns, int rows);
void tm_win_free(Tm_window* win);

void tm_get_scrsize(int* x, int* y);
void tm_set_scrsize(int x, int y);

void tm_get_winsize(Tm_window* win, int* columns, int* rows);
void tm_get_winpos(Tm_window* win, int* position_x, int* position_y);

int tm_win_modify(Tm_window* win, int x, int y, int columns, int rows);

void tm_win_update(Tm_window* win);

int tm_win_print_str(Tm_window* win, char* text);
int tm_win_print_ch(Tm_window* win, char ch);

int tm_win_cursor(Tm_window* win, int x, int y);

void tm_init();
void tm_exit();

void tm_win_border(Tm_window* win);
void tm_win_parent(Tm_window* parent, Tm_window* child);

int tm_win_clear(Tm_window* win);

#define tm_update() tm_win_update(default_win);
#define tm_print_str(text) tm_win_print_str(default_win, text);
#define tm_print_ch(ch) tm_win_print_ch(default_win, ch)
#define tm_cursor(x, y) tm_win_cursor(default_win, x, y);
#define tm_update() tm_win_update(default_win);
#endif

