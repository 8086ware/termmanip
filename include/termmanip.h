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

#define TM_ATTRIB_FG_MASK 0b00000000111111110000000000000000
#define TM_ATTRIB_BG_MASK 0b11111111000000000000000000000000

#define TM_ATTRIB_FG_BLACK 0b00000000000111100000000000000000
#define TM_ATTRIB_FG_RED 0b00000000000111110000000000000000
#define TM_ATTRIB_FG_GREEN 0b00000000001000000000000000000000
#define TM_ATTRIB_FG_YELLOW 0b00000000001000010000000000000000
#define TM_ATTRIB_FG_BLUE 0b00000000001000100000000000000000
#define TM_ATTRIB_FG_MAGENTA 0b00000000001000110000000000000000
#define TM_ATTRIB_FG_CYAN 0b00000000001001000000000000000000
#define TM_ATTRIB_FG_WHITE 0b00000000001001010000000000000000

#define TM_ATTRIB_BG_BLACK 0b00101000000000000000000000000000
#define TM_ATTRIB_BG_RED 0b00101001000000000000000000000000
#define TM_ATTRIB_BG_GREEN 0b00101010000000000000000000000000
#define TM_ATTRIB_BG_YELLOW 0b00101011000000000000000000000000
#define TM_ATTRIB_BG_BLUE 0b00101100000000000000000000000000
#define TM_ATTRIB_BG_MAGENTA 0b00101101000000000000000000000000
#define TM_ATTRIB_BG_CYAN 0b00101110000000000000000000000000
#define TM_ATTRIB_BG_WHITE 0b00101111000000000000000000000000

#define TM_ATTRIB_FG_BRIGHTBLACK 0b00000000010110100000000000000000
#define TM_ATTRIB_FG_BRIGHTRED 0b00000000010110110000000000000000
#define TM_ATTRIB_FG_BRIGHTGREEN 0b00000000010111000000000000000000
#define TM_ATTRIB_FG_BRIGHTYELLOW 0b00000000010111010000000000000000 
#define TM_ATTRIB_FG_BRIGHTBLUE 0b00000000010111100000000000000000
#define TM_ATTRIB_FG_BRIGHTMAGENTA 0b00000000010111110000000000000000
#define TM_ATTRIB_FG_BRIGHTCYAN 0b00000000011000000000000000000000
#define TM_ATTRIB_FG_BRIGHTWHITE 0b00000000011000010000000000000000


#define TM_ATTRIB_BG_BRIGHTBLACK 0b01100100000000000000000000000000
#define TM_ATTRIB_BG_BRIGHTRED 0b01100101000000000000000000000000
#define TM_ATTRIB_BG_BRIGHTGREEN 0b01100110000000000000000000000000
#define TM_ATTRIB_BG_BRIGHTYELLOW 0b01100111000000000000000000000000
#define TM_ATTRIB_BG_BRIGHTBLUE 0b01101000000000000000000000000000
#define TM_ATTRIB_BG_BRIGHTMAGENTA 0b01101001000000000000000000000000
#define TM_ATTRIB_BG_BRIGHTCYAN 0b01101010000000000000000000000000
#define TM_ATTRIB_BG_BRIGHTWHITE 0b01101011000000000000000000000000

#define TM_ATTRIB_RESET                0b00000000000000000000000000000000

#define TM_ATTRIB_BOLD                 0b00000000000000000000000000000001
#define TM_ATTRIB_DIM                  0b00000000000000000000000000000010
#define TM_ATTRIB_ITALIC               0b00000000000000000000000000000100
#define TM_ATTRIB_UNDERLINE            0b00000000000000000000000000001000
#define TM_ATTRIB_BLINKING             0b00000000000000000000000000010000
#define TM_ATTRIB_HIGHLIGHT            0b00000000000000000000000000100000
#define TM_ATTRIB_HIDDEN               0b00000000000000000000000001000000
#define TM_ATTRIB_STRIKE               0b00000000000000000000000010000000
#define TM_ATTRIB_ALTERNATE            0b00000000000000000000000100000000
#define TM_ATTRIB_MAIN                 0b00000000000000000000001000000000

#define TM_FLAG_RAW  0b00000010
#define TM_FLAG_ECHO 0b00000001

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

int tm_win_input_ch(Tm_window* win);
int tm_win_input_str(Tm_window* win, char* str, int max_size);

Tm_window* tm_win_button(Tm_window* win, int x, int y, int columns, int rows, char* text);
Tm_window* tm_win_button_select(Tm_window* win);

int tm_win_dialog(Tm_window* win, char* title, char* message, const int option_amount, ...);

int tm_win_clear(Tm_window* win);

int tm_error();

int tm_inputblock(int state);

#define tm_print(text, ...) tm_win_print(default_win, text, ## __VA_ARGS__)
#define tm_cursor(x, y) tm_win_cursor(default_win, x, y)
#define tm_update() tm_win_update(default_win)
#define tm_fill(from_x, from_y, to_x, to_y, ch, attrib) tm_win_fill(default_win, from_x, from_y, to_x, to_y, ch, attrib)
#define tm_attrib(attrib) tm_win_attrib(default_win, attrib)
#define tm_background(attrib) tm_win_background(default_win, attrib)
#define tm_input_str(str, max_size) tm_win_input_str(default_win, str, max_size)
#define tm_input_ch() tm_win_input_ch(default_win)
#define tm_dialog(title, message, option_amount, ...) tm_win_dialog(default_win, title, message, option_amount, ## __VA_ARGS__)
#define tm_echo(state) tm_win_echo(default_win, state)
#define tm_raw(state) tm_win_raw(default_win, state)
#define tm_button(x, y, columns, rows, text) tm_win_button(default_win, x, y, columns, rows, text)
#define tm_button_select() tm_win_button_select(default_win);
#define tm_clear() tm_win_clear(default_win)

#endif

