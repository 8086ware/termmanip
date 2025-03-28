#ifndef TERMMANIP_H
#define TERMMANIP_H

#define TM_ERROR -1

// Error types
enum Tm_return {TM_INVALID_CURSOR = 1, TM_INVALID_WINDOW_SIZE = 4, TM_OUT_OF_MEM = 5, TM_COULDNT_INIT_TERM = 6};

// Child window types

enum Tm_window_type {
	TM_WIN_NONE, 
	TM_WIN_BUTTON,
	TM_WIN_DIALOG,
};

// Tm_char attributes

enum Tm_attrib {
	TM_ATTRIB_FG_MASK =            0b00000000111111110000000000000000,
	TM_ATTRIB_BG_MASK =            0b11111111000000000000000000000000,

	TM_ATTRIB_FG_BLACK =           0b00000000000111100000000000000000,
	TM_ATTRIB_FG_RED =             0b00000000000111110000000000000000,
	TM_ATTRIB_FG_GREEN =           0b00000000001000000000000000000000,
	TM_ATTRIB_FG_YELLOW =          0b00000000001000010000000000000000,
	TM_ATTRIB_FG_BLUE   =          0b00000000001000100000000000000000,
	TM_ATTRIB_FG_MAGENTA =         0b00000000001000110000000000000000,
	TM_ATTRIB_FG_CYAN   =          0b00000000001001000000000000000000,
	TM_ATTRIB_FG_WHITE  =          0b00000000001001010000000000000000,

	TM_ATTRIB_BG_BLACK  =          0b00101000000000000000000000000000,
	TM_ATTRIB_BG_RED    =          0b00101001000000000000000000000000,
	TM_ATTRIB_BG_GREEN  =          0b00101010000000000000000000000000,
	TM_ATTRIB_BG_YELLOW =          0b00101011000000000000000000000000,
	TM_ATTRIB_BG_BLUE   =          0b00101100000000000000000000000000,
	TM_ATTRIB_BG_MAGENTA =         0b00101101000000000000000000000000,
	TM_ATTRIB_BG_CYAN   =          0b00101110000000000000000000000000,
	TM_ATTRIB_BG_WHITE  =          0b00101111000000000000000000000000,

	TM_ATTRIB_FG_BRIGHTBLACK   =   0b00000000010110100000000000000000,
	TM_ATTRIB_FG_BRIGHTRED     =   0b00000000010110110000000000000000,
	TM_ATTRIB_FG_BRIGHTGREEN   =   0b00000000010111000000000000000000,
	TM_ATTRIB_FG_BRIGHTYELLOW  =   0b00000000010111010000000000000000,
	TM_ATTRIB_FG_BRIGHTBLUE    =   0b00000000010111100000000000000000,
	TM_ATTRIB_FG_BRIGHTMAGENTA =   0b00000000010111110000000000000000,
	TM_ATTRIB_FG_BRIGHTCYAN    =   0b00000000011000000000000000000000,
	TM_ATTRIB_FG_BRIGHTWHITE   =   0b00000000011000010000000000000000,

	TM_ATTRIB_BG_BRIGHTBLACK   =   0b01100100000000000000000000000000,
	TM_ATTRIB_BG_BRIGHTRED     =   0b01100101000000000000000000000000,
	TM_ATTRIB_BG_BRIGHTGREEN   =   0b01100110000000000000000000000000,
	TM_ATTRIB_BG_BRIGHTYELLOW  =   0b01100111000000000000000000000000,
	TM_ATTRIB_BG_BRIGHTBLUE     =  0b01101000000000000000000000000000,
	TM_ATTRIB_BG_BRIGHTMAGENTA  =  0b01101001000000000000000000000000,
	TM_ATTRIB_BG_BRIGHTCYAN   =    0b01101010000000000000000000000000,
	TM_ATTRIB_BG_BRIGHTWHITE  =    0b01101011000000000000000000000000,

	TM_ATTRIB_BOLD            =    0b00000000000000000000000000000001,
	TM_ATTRIB_DIM             =    0b00000000000000000000000000000010,
	TM_ATTRIB_ITALIC          =    0b00000000000000000000000000000100,
	TM_ATTRIB_UNDERLINE       =    0b00000000000000000000000000001000,
	TM_ATTRIB_BLINKING        =    0b00000000000000000000000000010000,
	TM_ATTRIB_HIGHLIGHT       =    0b00000000000000000000000000100000,
	TM_ATTRIB_HIDDEN          =    0b00000000000000000000000001000000,
	TM_ATTRIB_STRIKE          =    0b00000000000000000000000010000000,
	TM_ATTRIB_ALTERNATE       =    0b00000000000000000000000100000000,

	TM_ATTRIB_ALL             =    0b11111111111111111111111111111111
};

// Scroll directions

enum Tm_scroll {
	TM_SCROLL_UP = 0,
	TM_SCROLL_DOWN = 1,
	TM_SCROLL_RIGHT = 2,
	TM_SCROLL_LEFT = 3,
};

// Window flags

enum Tm_flags {
	TM_FLAG_ECHO =           0b0000000000000010, 
	TM_FLAG_CURSOR_VISIBLE = 0b0000000000000100,
	TM_FLAG_SCROLL =         0b0000000000001000, 
	TM_FLAG_SHADOW =         0b0000000000010000, 
	TM_FLAG_MOUSE_INPUT =    0b0000000000100000, 
	TM_FLAG_TERMINAL_INPUT = 0b0000000001000000, 
	TM_FLAG_WRAP_TEXT =      0b0000000010000000, 
	TM_FLAG_WINDOW_SELECT =  0b0000000100000000, 
	TM_FLAG_BORDER       =   0b0000001000000000, 
	TM_FLAG_ALL =            0b1111111111111111
};

typedef enum {TM_KEY_NUL = 0, TM_KEY_SOH = 1, TM_KEY_STX = 2, TM_KEY_ETX = 3, TM_KEY_EOT = 4, TM_KEY_ENQ = 5, TM_KEY_ACK = 6, TM_KEY_BEL = '\a', TM_KEY_BS = '\b', TM_KEY_TAB = '\t', TM_KEY_LF = '\n', TM_KEY_VT = '\v', TM_KEY_FF = '\f', TM_KEY_CR = '\r', TM_KEY_SO = 14, TM_KEY_SI = 15, TM_KEY_DLE = 16, TM_KEY_DC1 = 17, TM_KEY_DC2 = 18, TM_KEY_DC3 = 19, TM_KEY_DC4 = 20, TM_KEY_NAK = 21, TM_KEY_SYN = 22, TM_KEY_ETB = 23, TM_KEY_CAN = 24, TM_KEY_EM = 25, TM_KEY_SUB = 26, TM_KEY_ESC = 27, TM_KEY_FS = 28, TM_KEY_GS = 29, TM_KEY_RS = 30, TM_KEY_US = 31, TM_KEY_SP = 32, TM_KEY_EXCLAMATION = '!', TM_KEY_DQUOTE = '\"', TM_KEY_HASHTAG = '#', TM_KEY_DOLLAR = '$', TM_KEY_PERCENT = '%', TM_KEY_AMPERSAND = '&', TM_KEY_QUOTE = '\'', TM_KEY_PARENTHESES_LEFT = '(', TM_KEY_PARENTHESES_RIGHT = ')', TM_KEY_ASTERISK = '*', TM_KEY_PLUS = '+', TM_KEY_COMMA = ',', TM_KEY_DASH = '-', TM_KEY_PERIOD = '.', TM_KEY_SLASH = '/', TM_KEY_ZERO = '0', TM_KEY_ONE = '1', TM_KEY_TWO = '2', TM_KEY_THREE = '3', TM_KEY_FOUR = '4', TM_KEY_FIVE = '5', TM_KEY_SIX = '6', TM_KEY_SEVEN = '7', TM_KEY_EIGHT = '8', TM_KEY_NINE = '9', TM_KEY_COLON = ':', TM_KEY_SEMICOLON = ';', TM_KEY_LESS_THAN = '<', TM_KEY_EQUAL = '=', TM_KEY_MORE_THAN = '>', TM_KEY_QUESTION = '?', TM_KEY_AT = '@', TM_KEY_UP_A = 'A', TM_KEY_UP_B = 'B', TM_KEY_UP_C = 'C', TM_KEY_UP_D = 'D', TM_KEY_UP_E = 'E', TM_KEY_UP_F = 'F', TM_KEY_UP_G = 'G', TM_KEY_UP_H = 'H', TM_KEY_UP_I = 'I', TM_KEY_UP_J = 'J', TM_KEY_UP_K = 'K', TM_KEY_UP_L = 'L', TM_KEY_UP_M = 'M', TM_KEY_UP_N = 'N', TM_KEY_UP_O = 'O', TM_KEY_UP_P = 'P', TM_KEY_UP_Q = 'Q', TM_KEY_UP_R = 'R', TM_KEY_UP_S = 'S', TM_KEY_UP_T = 'T', TM_KEY_UP_U = 'U', TM_KEY_UP_V = 'V', TM_KEY_UP_W = 'W', TM_KEY_UP_X = 'X', TM_KEY_UP_Y = 'Y', TM_KEY_UP_Z = 'Z', TM_KEY_BRACKET_LEFT = '[', TM_KEY_BACKSLASH = '\\', TM_KEY_BRACKET_RIGHT = ']', TM_KEY_CARET = '^', TM_KEY_UNDERSCORE = '_', TM_KEY_BACKTICK = '`', TM_KEY_A = 'a', TM_KEY_B = 'b', TM_KEY_C = 'c', TM_KEY_D = 'd', TM_KEY_E = 'e', TM_KEY_F = 'f', TM_KEY_G = 'g', TM_KEY_H = 'h', TM_KEY_I = 'i', TM_KEY_J = 'j', TM_KEY_K = 'k', TM_KEY_L = 'l', TM_KEY_M = 'm', TM_KEY_N = 'n', TM_KEY_O = 'o', TM_KEY_P = 'p', TM_KEY_Q = 'q', TM_KEY_R = 'r', TM_KEY_S = 's', TM_KEY_T = 't', TM_KEY_U = 'u', TM_KEY_V = 'v', TM_KEY_W = 'w', TM_KEY_X = 'x', TM_KEY_Y = 'y', TM_KEY_Z = 'z', TM_KEY_CURLY_BRACKET_LEFT = '{', TM_KEY_PIPE = '|', TM_KEY_CURLY_BRACKET_RIGHT = '}', TM_KEY_TILDE = '~', TM_KEY_DEL = 127, TM_KEY_UP = 128, TM_KEY_DOWN = 129, TM_KEY_RIGHT = 130, TM_KEY_LEFT = 131, TM_KEY_F1 = 132, TM_KEY_F2 = 133, TM_KEY_F3 = 134, TM_KEY_F4 = 135, TM_KEY_F5 = 136, TM_KEY_F6 = 137, TM_KEY_F7 = 138, TM_KEY_F8 = 139, TM_KEY_F9 = 140, TM_KEY_F10 = 141, TM_KEY_F11 = 142, TM_KEY_F12 = 143, TM_KEY_HOME = 144, TM_KEY_END = 145, TM_KEY_INSERT = 146, TM_KEY_PG_UP = 147, TM_KEY_PG_DOWN = 148, TM_KEY_DELETE = 149,  TM_KEY_NONE = 150} Tmkey_T;

#include <stdint.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#endif

typedef struct {
	uint32_t attrib;
	char disp;
} Tm_char;

// Tm_terminal structure contains the physical entire terminal which is the columns and rows of the terminal. It has the pending changes which is an array with all
// the characters and attributes to be written at an x,y, it has an attrib variable which identifies the last attribute used, an output char array which is
// the output to be put on terminal (usually a bunch of ansi escape codes), uint16_t flags which is the last window updated flags.

typedef struct Tm_window Tm_window; // Struct prototype to include Tm_window in Tm_terminal

typedef struct {
	_Bool ctrl_down;
	_Bool alt_down;
	_Bool shift_down;

	_Bool terminal_resized;

	Tmkey_T ctrl_character;
	Tmkey_T key;

	_Bool mouse_moved;

	_Bool mouse_left;
	_Bool mouse_right;
	_Bool mouse_middle;

	_Bool mouse_down;

	_Bool scroll_up;
	_Bool scroll_down;

	int mouse_x;
	int mouse_y;

	Tm_window* win_selected;
} Tm_input;

// Tm_input structure holds input information returned by tm_win_input

typedef struct {
	int columns, rows;

   	Tm_char* buffer;
	Tm_char* physical_buffer;

	int cursor_x, cursor_y;

	int last_updated_x, last_updated_y;

	enum Tm_attrib attrib;

	char* output;
	int output_len;

	uint16_t flags;
#ifdef _WIN32
	DWORD og_input_mode;
	DWORD og_output_mode;
#else
	struct termios og_term;
	int signal_fd;
#endif
	_Bool resized;
	int tm_return_number;
	
	Tm_window* last_updated_window;

	Tm_window** windows;
	int window_amount;
	
	int selected_window_id;
} Tm_terminal;

// Tm_window structure is a very important structure. It has the position x and y of the window, the columns and rows, the cursor position, its parent and children (if it has any),
// the buffer containing its contents, a physical buffer to represent what has been copied onto the terminal, its flags and its current attrib.

typedef struct Tm_window {
	Tm_terminal* terminal;
	int position_x, position_y, columns, rows;
	int buffer_position_x, buffer_position_y, buffer_columns, buffer_rows;
	int cursor_x, cursor_y;

	char* name;
	int name_length;

	struct Tm_window* parent;
	struct Tm_window** children;

	enum Tm_window_type type;

	int children_amount;

	Tm_char* buffer;

	struct Tm_window* physical_window;

	Tm_char background_tm_char;
	
	enum Tm_flags flags;

	enum Tm_attrib attrib;

	int input_timeout;

	int wrapped_lines;

	_Bool update;

	_Bool selectable;
} Tm_window;

Tm_terminal* tm_terminal();
int tm_terminal_free(Tm_terminal* terminal);
// Create and free terminals

Tm_window* tm_window(Tm_terminal* terminal, char* name, int x, int y, int columns, int rows, Tm_window* parent, enum Tm_window_type type, int extra_arg_count, ...); // Creates new window
int tm_win_free(Tm_window* win); // Frees and deletes a window

void tm_get_termsize(int* x, int* y); // Gets the terminal size

int tm_win_get_cursor_x(Tm_window* win);
int tm_win_get_cursor_y(Tm_window* win);

int tm_win_get_columns(Tm_window* win); 
int tm_win_get_rows(Tm_window* win); 
									 
int tm_win_get_pos_x(Tm_window* win);
int tm_win_get_pos_y(Tm_window* win);

int tm_win_get_buffer_columns(Tm_window* win);
int tm_win_get_buffer_rows(Tm_window* win);

int tm_win_get_buffer_pos_x(Tm_window* win);
int tm_win_get_buffer_pos_y(Tm_window* win);

Tm_char tm_win_get_background(Tm_window* win);

int tm_win_modify(Tm_window* win, int x, int y, int columns, int rows, _Bool resize_buffer); // Modifies a windows x, y, columns and rows

int tm_terminal_update(Tm_terminal* terminal); // Puts the internal terminal onto the terminal

int tm_win_putch(Tm_window* win, char ch, uint32_t attrib); // Put a char at x, y and an attribute
int tm_win_puts(Tm_window * win, char* str, uint32_t attrib); // Put a string at x, y and an attribute
int tm_win_print(Tm_window* win, char* fmt, ...); // Print at current window cursor position

int tm_win_cursor(Tm_window* win, int x, int y); // Set window cursor position

int tm_win_parent(Tm_window* parent, Tm_window* child); // Make child be a child to parent window

void tm_win_fill(Tm_window* win, int from_x, int from_y, int to_x, int to_y, char ch, uint32_t attrib); // Fill from from_x, from_y to to_x, to_y with ch and attrib

void tm_win_attrib(Tm_window* win, enum Tm_attrib attrib, int state); // Set the window attribute
enum Tm_attrib tm_win_get_attrib(Tm_window* win); // Get the window attribute

void tm_win_background(Tm_window* win, char ch, uint32_t attrib); // Set the window background

Tm_input tm_win_input(Tm_window* win); // Get a single char and return it
void tm_win_input_str(Tm_window* win, char* str, int max_size); // Get a string
void tm_win_input_strf(Tm_window* win, char* str, ...);

void tm_win_clear(Tm_window* win); // Clear win

int tm_return(Tm_terminal* terminal); // Return the most recent error

int tm_win_scroll(Tm_window* win, int amount, enum Tm_scroll direction); // Scroll window in certain direction. If no space is available, the window buffer extends itself.

enum Tm_flags tm_win_get_flags(Tm_window* win); // Returns the windows flags
void tm_win_flags(Tm_window* win, uint16_t flags, int state); // Adjusts the windows flags turning them on or off (can be combined with OR)

void tm_set_title(char* text); // Set the terminal title

void tm_win_input_timeout(Tm_window* win, int timeout); // Set the input timeout
														
int tm_win_update(Tm_window* win);
void tm_win_mark_for_update(Tm_window* win);

#endif
