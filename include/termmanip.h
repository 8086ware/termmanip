#ifndef TERMMANIP_H
#define TERMMANIP_H

#define TM_ERROR -1

// Error types
#define TM_INVALID_CURSOR 1
#define TM_INVALID_DIMENSIONS 2
#define TM_DIALOG_NO_OPTIONS 3
#define TM_WIN_NULL 4

// Child window types
#define TM_CHILD_NONE 0
#define TM_CHILD_NORMAL 1
#define TM_CHILD_BUTTON 2

#define TM_ATTRIB_FG_MASK              0b00000000111111110000000000000000
#define TM_ATTRIB_BG_MASK              0b11111111000000000000000000000000

#define TM_ATTRIB_FG_BLACK             0b00000000000111100000000000000000
#define TM_ATTRIB_FG_RED               0b00000000000111110000000000000000
#define TM_ATTRIB_FG_GREEN             0b00000000001000000000000000000000
#define TM_ATTRIB_FG_YELLOW            0b00000000001000010000000000000000
#define TM_ATTRIB_FG_BLUE              0b00000000001000100000000000000000
#define TM_ATTRIB_FG_MAGENTA           0b00000000001000110000000000000000
#define TM_ATTRIB_FG_CYAN              0b00000000001001000000000000000000
#define TM_ATTRIB_FG_WHITE             0b00000000001001010000000000000000

#define TM_ATTRIB_BG_BLACK             0b00101000000000000000000000000000
#define TM_ATTRIB_BG_RED               0b00101001000000000000000000000000
#define TM_ATTRIB_BG_GREEN             0b00101010000000000000000000000000
#define TM_ATTRIB_BG_YELLOW            0b00101011000000000000000000000000
#define TM_ATTRIB_BG_BLUE              0b00101100000000000000000000000000
#define TM_ATTRIB_BG_MAGENTA           0b00101101000000000000000000000000
#define TM_ATTRIB_BG_CYAN              0b00101110000000000000000000000000
#define TM_ATTRIB_BG_WHITE             0b00101111000000000000000000000000

#define TM_ATTRIB_FG_BRIGHTBLACK       0b00000000010110100000000000000000
#define TM_ATTRIB_FG_BRIGHTRED         0b00000000010110110000000000000000
#define TM_ATTRIB_FG_BRIGHTGREEN       0b00000000010111000000000000000000
#define TM_ATTRIB_FG_BRIGHTYELLOW      0b00000000010111010000000000000000 
#define TM_ATTRIB_FG_BRIGHTBLUE        0b00000000010111100000000000000000
#define TM_ATTRIB_FG_BRIGHTMAGENTA     0b00000000010111110000000000000000
#define TM_ATTRIB_FG_BRIGHTCYAN        0b00000000011000000000000000000000
#define TM_ATTRIB_FG_BRIGHTWHITE       0b00000000011000010000000000000000

#define TM_ATTRIB_BG_BRIGHTBLACK       0b01100100000000000000000000000000
#define TM_ATTRIB_BG_BRIGHTRED         0b01100101000000000000000000000000
#define TM_ATTRIB_BG_BRIGHTGREEN       0b01100110000000000000000000000000
#define TM_ATTRIB_BG_BRIGHTYELLOW      0b01100111000000000000000000000000
#define TM_ATTRIB_BG_BRIGHTBLUE        0b01101000000000000000000000000000
#define TM_ATTRIB_BG_BRIGHTMAGENTA     0b01101001000000000000000000000000
#define TM_ATTRIB_BG_BRIGHTCYAN        0b01101010000000000000000000000000
#define TM_ATTRIB_BG_BRIGHTWHITE       0b01101011000000000000000000000000

#define TM_ATTRIB_BOLD                 0b00000000000000000000000000000001
#define TM_ATTRIB_DIM                  0b00000000000000000000000000000010
#define TM_ATTRIB_ITALIC               0b00000000000000000000000000000100
#define TM_ATTRIB_UNDERLINE            0b00000000000000000000000000001000
#define TM_ATTRIB_BLINKING             0b00000000000000000000000000010000
#define TM_ATTRIB_HIGHLIGHT            0b00000000000000000000000000100000
#define TM_ATTRIB_HIDDEN               0b00000000000000000000000001000000
#define TM_ATTRIB_STRIKE               0b00000000000000000000000010000000
#define TM_ATTRIB_RESET                0b00000000000000000000010000000000

// Window flags

#define TM_FLAG_RAW            0b0000000000000001
#define TM_FLAG_ECHO           0b0000000000000010
#define TM_FLAG_CURSOR_VISIBLE 0b0000000000000100

#include <stdint.h>
#include <termios.h>

typedef struct {
	uint32_t attrib;
	char disp;
} Tm_char;

// Tm_screen structure contains the physical entire screen which is the columns and rows of the terminal. It has the pending changes which is an array with all
// the characters and attributes to be written at an x,y, it has an attrib variable which identifies the last attribute used, an output char array which is
// the output to be put on screen (usually a bunch of ansi escape codes), uint16_t flags which is the last window updated flags.

typedef struct {
	int columns, rows;

	Tm_char* buffer;
	Tm_char* physical_buffer;

	int cursor_x, cursor_y;

	uint32_t attrib;

	char* output;
	int output_len;

	uint16_t flags;
} Tm_screen;

// Tm_window structure is a very important structure. It has the position x and y of the window, the columns and rows, the cursor position, its parent and children (if it has any),
// the buffer containing its contents, a physical buffer to represent what has been copied onto the screen, its flags and its current attrib.

typedef struct Tm_window {
	int position_x, position_y, columns, rows;
	int cursor_x, cursor_y;

	struct Tm_window* parent;
	struct Tm_window** children;

	int child_type;

	int children_amount;

	Tm_char* buffer;
	
	uint16_t flags;

	uint32_t attrib;
} Tm_window;

extern Tm_window* default_win;
extern Tm_screen* screen;

extern int tm_error_number;
extern struct termios og_term;

Tm_window* tm_window(int x, int y, int columns, int rows); // Creates new window
void tm_win_free(Tm_window* win); // Frees and deletes a window

void tm_get_scrsize(int* x, int* y); // Gets the screensize
void tm_set_scrsize(int x, int y); // Sets the screensize

void tm_get_winsize(Tm_window* win, int* columns, int* rows); // Gets a windows size
void tm_get_winpos(Tm_window* win, int* position_x, int* position_y); // Gets a windows position

int tm_win_modify(Tm_window* win, int x, int y, int columns, int rows); // Modifies a windows x, y, columns and rows

void tm_win_write_to_screen(Tm_window* win); // Writes the window to the screen structure but doesn't display to the actual terminal
void tm_screen_update(); // Puts the internal screen onto the terminal
void tm_win_update(Tm_window* win); // Updates a window by using tm_win_write_to_screen and tm_screen_update

int tm_win_putch(Tm_window* win, int x, int y, char ch, uint32_t attrib); // Put a char at x, y and an attribute
int tm_win_puts(Tm_window * win, int x, int y, char* str, uint32_t attrib); // Put a string at x, y and an attribute
int tm_win_print(Tm_window* win, char* fmt, ...); // Print at current window cursor position

int tm_win_cursor(Tm_window* win, int x, int y); // Set window cursor position
int tm_win_cursor_visible(Tm_window* win, int state); // Depending on state is false or true will turn on or off the cursor visibility

void tm_win_echo(Tm_window* win, int state); // Depending on state is false or true will turn on or off input echo
void tm_win_raw(Tm_window* win, int state); // Depending on state is false or true will turn on or off input raw mode (won't return as soon as it gets a character)

void tm_init(); // Initalize termmanip
void tm_exit(); // Exit termmanip

int tm_win_border(Tm_window* win); // Border a window
int tm_win_parent(Tm_window* parent, Tm_window* child, int type); // Make child be a child to parent window

int tm_win_fill(Tm_window* win, int from_x, int from_y, int to_x, int to_y, char ch, uint32_t attrib); // Fill from from_x, from_y to to_x, to_y with ch and attrib

void tm_win_attrib(Tm_window* win, uint32_t attrib); // Set the window attribute

int tm_win_background(Tm_window* win, uint32_t attrib); // Set the window background

int tm_win_input_ch(Tm_window* win); // Get a single char and return it
int tm_win_input_str(Tm_window* win, char* str, int max_size); // Get a string

Tm_window* tm_win_button(Tm_window* win, int x, int y, int columns, int rows, char* text); // Put a button in the window
Tm_window* tm_win_button_select(Tm_window* win); // Start selecting buttons

int tm_win_dialog(Tm_window* win, char* title, char* message, const int option_amount, ...); // Make a new dialog in win

int tm_win_clear(Tm_window* win); // Clear win

int tm_error(); // Return the most recent error

int tm_inputblock(int state); // Depending on state is false or true will turn on or off input blocking which makes tm_win_input_ch return without pressing a single key

//Bunch of macros that serve the same functionality as other functions except they act upon the default window
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

