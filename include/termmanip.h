#ifndef TERMMANIP_H
#define TERMMANIP_H

#define TM_WIN_NULL 1
#define TM_WIN_INVALID_DIMENSIONS 2
#define TM_INVALID_CURSOR 3
#define TM_WIN_CONTENTS_NULL 4

#define TM_ESC_ENTER_ALT_SCREEN "\x1b[?1049h"
#define TM_ESC_LEAVE_ALT_SCREEN "\x1b[?1049l"

#define TM_ATTRIB_FG_BLACK 30
#define TM_ATTRIB_FG_RED 31
#define TM_ATTRIB_FG_GREEN 32
#define TM_ATTRIB_FG_YELLOW 33
#define TM_ATTRIB_FG_BLUE 34
#define TM_ATTRIB_FG_MAGENTA 35
#define TM_ATTRIB_FG_CYAN 36
#define TM_ATTRIB_FG_WHITE 37

#define TM_ATTRIB_BG_BLACK 40
#define TM_ATTRIB_BG_RED 41
#define TM_ATTRIB_BG_GREEN 42
#define TM_ATTRIB_BG_YELLOW 43
#define TM_ATTRIB_BG_BLUE 44
#define TM_ATTRIB_BG_MAGENTA 45
#define TM_ATTRIB_BG_CYAN 46
#define TM_ATTRIB_BG_WHITE 47

#define TM_ATTRIB_FG_BRIGHTBLACK 90
#define TM_ATTRIB_FG_BRIGHTRED 91
#define TM_ATTRIB_FG_BRIGHTGREEN 92
#define TM_ATTRIB_FG_BRIGHTYELLOW 93
#define TM_ATTRIB_FG_BRIGHTBLUE 94
#define TM_ATTRIB_FG_BRIGHTMAGENTA 95
#define TM_ATTRIB_FG_BRIGHTCYAN 96
#define TM_ATTRIB_FG_BRIGHTWHITE 97

#define TM_ATTRIB_BG_BRIGHTBLACK 100
#define TM_ATTRIB_BG_BRIGHTRED 101
#define TM_ATTRIB_BG_BRIGHTGREEN 102
#define TM_ATTRIB_BG_BRIGHTYELLOW 103
#define TM_ATTRIB_BG_BRIGHTBLUE 104
#define TM_ATTRIB_BG_BRIGHTMAGENTA 105
#define TM_ATTRIB_BG_BRIGHTCYAN 106
#define TM_ATTRIB_BG_BRIGHTWHITE 107

#define TM_ATTRIB_RESET 0

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

int tm_win_fill(Tm_window* win, int from_x, int from_y, int to_x, int to_y, char ch, int attrib);

void tm_win_attrib(Tm_window* win, int attrib);

void tm_win_background(Tm_window* win, int attrib);

void tm_echo(int state);
void tm_rawinput(int state);

char tm_input_ch();

#define tm_update() tm_win_update(default_win)
#define tm_print_str(text) tm_win_print_str(default_win, text)
#define tm_print_ch(ch) tm_win_print_ch(default_win, ch)
#define tm_cursor(x, y) tm_win_cursor(default_win, x, y)
#define tm_update() tm_win_update(default_win)
#define tm_fill(from_x, from_y, to_x, to_y, ch, attrib) tm_win_fill(default_win, from_x, from_y, to_x, to_y, ch, attrib)
#define tm_attrib(attrib) tm_win_attrib(default_win, attrib)
#define tm_background(attrib) tm_win_background(default_win, attrib)
#endif

