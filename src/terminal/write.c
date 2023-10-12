#include "termmanip.h"
#include "terminal.h"

void terminal_write(int x, int y, char ch, uint32_t attrib) {
	int position = y * terminal->columns + x;

	if(position > terminal->columns * terminal->rows - 1 || position < 0) {
		return;
	}

	y = position / terminal->columns;
	x = position % terminal->columns;

	if(ch == terminal->buffer[position].disp && attrib == terminal->buffer[position].attrib) {
		return;
	}

	terminal->buffer[position].disp = ch;
	terminal->buffer[position].attrib = attrib;

	if(terminal->attrib != attrib) {
		if(attrib & TM_ATTRIB_ALTERNATE && (terminal->attrib & TM_ATTRIB_ALTERNATE) == 0) {
			terminal_append_output("\x1b(0");
		}

		else if((attrib & TM_ATTRIB_ALTERNATE) == 0 && terminal->attrib & TM_ATTRIB_ALTERNATE) {
			terminal_append_output("\x1b(B");
		}

		if(attrib & TM_ATTRIB_BOLD && (terminal->attrib & TM_ATTRIB_BOLD) == 0) {
			terminal_append_output("\x1b[1m");
		}

		else if((attrib & TM_ATTRIB_BOLD) == 0 && terminal->attrib & TM_ATTRIB_BOLD) {
			terminal_append_output("\x1b[22m");
		}

		if(attrib & TM_ATTRIB_DIM && (terminal->attrib & TM_ATTRIB_DIM) == 0) {
			terminal_append_output("\x1b[2m");
		}

		else if((attrib & TM_ATTRIB_DIM) == 0 && terminal->attrib & TM_ATTRIB_DIM) {
			terminal_append_output("\x1b[22m");
		}

		if(attrib & TM_ATTRIB_ITALIC && (terminal->attrib & TM_ATTRIB_ITALIC) == 0) {
			terminal_append_output("\x1b[3m");
		}

		else if((attrib & TM_ATTRIB_ITALIC) == 0 && terminal->attrib & TM_ATTRIB_ITALIC) {
			terminal_append_output("\x1b[23m");
		}

		if(attrib & TM_ATTRIB_UNDERLINE && (terminal->attrib & TM_ATTRIB_UNDERLINE) == 0) {
			terminal_append_output("\x1b[4m");
		}

		else if((attrib & ~TM_ATTRIB_UNDERLINE) == 0 && terminal->attrib & TM_ATTRIB_UNDERLINE) {
			terminal_append_output("\x1b[24m");
		}

		if(attrib & TM_ATTRIB_BLINKING && (terminal->attrib & TM_ATTRIB_BLINKING) == 0) {
			terminal_append_output("\x1b[5m");
		}

		else if((attrib & TM_ATTRIB_BLINKING) == 0 && terminal->attrib & TM_ATTRIB_BLINKING) {
			terminal_append_output("\x1b[25m");
		}

		if(attrib & TM_ATTRIB_HIGHLIGHT && (terminal->attrib & TM_ATTRIB_HIGHLIGHT) == 0) {
			terminal_append_output("\x1b[7m");
		}

		else if((attrib & TM_ATTRIB_HIGHLIGHT) == 0 && terminal->attrib & TM_ATTRIB_HIGHLIGHT) {
			terminal_append_output("\x1b[27m");
		}

		if(attrib & TM_ATTRIB_HIDDEN && (terminal->attrib & TM_ATTRIB_HIDDEN) == 0) {
			terminal_append_output("\x1b[8m");
		}

		else if((attrib & TM_ATTRIB_HIDDEN) == 0 && terminal->attrib & TM_ATTRIB_HIDDEN) {
			terminal_append_output("\x1b[28m");
		}

		if(attrib & TM_ATTRIB_STRIKE && (terminal->attrib & TM_ATTRIB_STRIKE) == 0) {
			terminal_append_output("\x1b[9m");
		}

		else if((attrib & TM_ATTRIB_STRIKE) == 0 && terminal->attrib & TM_ATTRIB_STRIKE) {
			terminal_append_output("\x1b[29m");
		}

		if(attrib & TM_ATTRIB_FG_MASK && (terminal->attrib & TM_ATTRIB_FG_MASK) != (attrib & TM_ATTRIB_FG_MASK)) {
			terminal_append_output("\x1b[%dm", (attrib & TM_ATTRIB_FG_MASK) >> 16);
		}

		else if((attrib & TM_ATTRIB_FG_MASK) == 0 && (terminal->attrib & TM_ATTRIB_FG_MASK) != 0) {
			terminal_append_output("\x1b[39m");
		}

		if(attrib & TM_ATTRIB_BG_MASK && (terminal->attrib & TM_ATTRIB_BG_MASK) != (attrib & TM_ATTRIB_BG_MASK)) {
			terminal_append_output("\x1b[%dm", (attrib & TM_ATTRIB_BG_MASK) >> 24);
		}

		else if((attrib & TM_ATTRIB_BG_MASK) == 0 && (terminal->attrib & TM_ATTRIB_BG_MASK) != 0) {
			terminal_append_output("\x1b[49m");
		}

		terminal->attrib = attrib;
	}

	if(x - terminal->last_updated_x != 1 || terminal->last_updated_y != y) {
		terminal_append_output("\x1b[%d;%dH", y + 1, x + 1);
	}

	terminal_append_output("%c", ch);

	terminal->last_updated_x = x;
	terminal->last_updated_y = y;
}

