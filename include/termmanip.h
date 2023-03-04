#ifndef TERMMANIP_H
#define TERMMANIP_H

#define TM_ERROR -1

#define TM_INVALID_CURSOR 1
#define TM_INVALID_DIMENSIONS 2
#define TM_DIALOG_NO_OPTIONS 3
#define TM_WIN_NULL 4

#define TM_CHILD_NONE 0
#define TM_CHILD_NORMAL 1
#define TM_CHILD_BUTTON 2

#define TM_ESC_ENTER_ALT_SCREEN "\x1b[?1049h"
#define TM_ESC_LEAVE_ALT_SCREEN "\x1b[?1049l"
#define TM_ESC_ENABLE_CURSOR "\x1b[?25h"
#define TM_ESC_DISABLE_CURSOR "\x1b[?25l"

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
#define TM_ATTRIB_BOLD 1

#define TM_FLAG_ECHO 0b10000000
#define TM_FLAG_RAW  0b01000000

#include <stddef.h>

typedef struct _Tm_window {
	int position_x, position_y, columns, rows;
	int cursor_x, cursor_y;

	struct _Tm_window* parent;
	struct _Tm_window** children;

	int child_type;

	int children_amount;

	char* contents;
	int content_len;

	unsigned char flags;
} Tm_window;

extern Tm_window* default_win;
extern int tm_error_number;

Tm_window* tm_window(int x, int y, int columns, int rows);
void tm_win_free(Tm_window* win);

void tm_get_scrsize(int* x, int* y);
void tm_set_scrsize(int x, int y);

void tm_get_winsize(Tm_window* win, int* columns, int* rows);
void tm_get_winpos(Tm_window* win, int* position_x, int* position_y);

int tm_win_modify(Tm_window* win, int x, int y, int columns, int rows);

void tm_win_update(Tm_window* win);

int tm_win_print(Tm_window* win, char* fmt, ...);

int tm_win_cursor(Tm_window* win, int x, int y);
int tm_win_cursor_visible(Tm_window* win, int state);

void tm_win_echo(Tm_window* win, int state);
void tm_win_raw(Tm_window* win, int state);

void tm_init();
void tm_exit();

int tm_win_border(Tm_window* win);
int tm_win_parent(Tm_window* parent, Tm_window* child, int type);

void tm_win_memclear(Tm_window* win);

int tm_win_fill(Tm_window* win, int from_x, int from_y, int to_x, int to_y, char ch, int attrib);

int tm_win_attrib(Tm_window* win, int attrib);

int tm_win_background(Tm_window* win, int attrib);

void tm_echo(int state);
void tm_rawinput(int state);

char tm_input_ch();
void tm_win_input_str(Tm_window* win, char* str, int max_size);

Tm_window* tm_win_button(Tm_window* win, int x, int y, int columns, int rows, char* text);
Tm_window* tm_win_button_select(Tm_window* win);

int tm_win_dialog(Tm_window* win, int x, int y, int columns, int rows, char* message, const int option_amount, ...);

int tm_win_clear(Tm_window* win);

int tm_error();

#define tm_print(text, ...) tm_win_print(default_win, text, ## __VA_ARGS__)
#define tm_cursor(x, y) tm_win_cursor(default_win, x, y)
#define tm_update() tm_win_update(default_win)
#define tm_fill(from_x, from_y, to_x, to_y, ch, attrib) tm_win_fill(default_win, from_x, from_y, to_x, to_y, ch, attrib)
#define tm_attrib(attrib) tm_win_attrib(default_win, attrib)
#define tm_background(attrib) tm_win_background(default_win, attrib)
#define tm_input_str(str, max_size) tm_win_input_str(default_win, str, max_size)
#define tm_dialog(x, y, columns, rows, message, option_amount, ...) tm_win_dialog(default_win, x, y, columns, rows, message, option_amount, ## __VA_ARGS__)
#define tm_echo(state) tm_win_echo(default_win, state)
#define tm_raw(state) tm_win_raw(default_win, state)
#define tm_button(x, y, columns, rows, text) tm_win_button(default_win, x, y, columns, rows, text)
#define tm_button_select() tm_win_button_select(default_win);
#define tm_clear() tm_win_clear(default_win)

#endif

