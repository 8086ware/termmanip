#include "append_output.h"
#include "termmanip.h"

void terminal_write(int x, int y, char ch, uint32_t attrib) {
	static int from_x = 0, from_y = 0;
	if(screen->attrib != attrib) {
		if(attrib & TM_ATTRIB_ALTERNATE && (screen->attrib & TM_ATTRIB_ALTERNATE) == 0) {
			append_output("\x1b(0");
		}

		else if((attrib & TM_ATTRIB_ALTERNATE) == 0 && screen->attrib & TM_ATTRIB_ALTERNATE) {
			append_output("\x1b(B");
		}

		if(attrib & TM_ATTRIB_BOLD && (screen->attrib & TM_ATTRIB_BOLD) == 0) {
			append_output("\x1b[1m");
		}

		else if((attrib & TM_ATTRIB_BOLD) == 0 && screen->attrib & TM_ATTRIB_BOLD) {
			append_output("\x1b[22m");
		}

		if(attrib & TM_ATTRIB_DIM && (screen->attrib & TM_ATTRIB_DIM) == 0) {
			append_output("\x1b[2m");
		}

		else if((attrib & TM_ATTRIB_DIM) == 0 && screen->attrib & TM_ATTRIB_DIM) {
			append_output("\x1b[22m");
		}

		if(attrib & TM_ATTRIB_ITALIC && (screen->attrib & TM_ATTRIB_ITALIC) == 0) {
			append_output("\x1b[3m");
		}

		else if((attrib & TM_ATTRIB_ITALIC) == 0 && screen->attrib & TM_ATTRIB_ITALIC) {
			append_output("\x1b[23m");
		}

		if(attrib & TM_ATTRIB_UNDERLINE && (screen->attrib & TM_ATTRIB_UNDERLINE) == 0) {
			append_output("\x1b[4m");
		}

		else if((attrib & ~TM_ATTRIB_UNDERLINE) == 0 && screen->attrib & TM_ATTRIB_UNDERLINE) {
			append_output("\x1b[24m");
		}

		if(attrib & TM_ATTRIB_BLINKING && (screen->attrib & TM_ATTRIB_BLINKING) == 0) {
			append_output("\x1b[5m");
		}

		else if((attrib & TM_ATTRIB_BLINKING) == 0 && screen->attrib & TM_ATTRIB_BLINKING) {
			append_output("\x1b[25m");
		}

		if(attrib & TM_ATTRIB_HIGHLIGHT && (screen->attrib & TM_ATTRIB_HIGHLIGHT) == 0) {
			append_output("\x1b[7m");
		}

		else if((attrib & TM_ATTRIB_HIGHLIGHT) == 0 && screen->attrib & TM_ATTRIB_HIGHLIGHT) {
			append_output("\x1b[27m");
		}

		if(attrib & TM_ATTRIB_HIDDEN && (screen->attrib & TM_ATTRIB_HIDDEN) == 0) {
			append_output("\x1b[8m");
		}

		else if((attrib & TM_ATTRIB_HIDDEN) == 0 && screen->attrib & TM_ATTRIB_HIDDEN) {
			append_output("\x1b[28m");
		}

		if(attrib & TM_ATTRIB_STRIKE && (screen->attrib & TM_ATTRIB_STRIKE) == 0) {
			append_output("\x1b[9m");
		}

		else if((attrib & TM_ATTRIB_STRIKE) == 0 && screen->attrib & TM_ATTRIB_STRIKE) {
			append_output("\x1b[29m");
		}

		if(attrib & TM_ATTRIB_FG_MASK && (screen->attrib & TM_ATTRIB_FG_MASK) != (attrib & TM_ATTRIB_FG_MASK)) {
			append_output("\x1b[%dm", (attrib & TM_ATTRIB_FG_MASK) >> 16);
		}

		else if((attrib & TM_ATTRIB_FG_MASK) == 0 && (screen->attrib & TM_ATTRIB_FG_MASK) != 0) {
			append_output("\x1b[39m");
		}

		if(attrib & TM_ATTRIB_BG_MASK && (screen->attrib & TM_ATTRIB_BG_MASK) != (attrib & TM_ATTRIB_BG_MASK)) {
			append_output("\x1b[%dm", (attrib & TM_ATTRIB_BG_MASK) >> 24);
		}

		else if((attrib & TM_ATTRIB_BG_MASK) == 0 && (screen->attrib & TM_ATTRIB_BG_MASK) != 0) {
			append_output("\x1b[49m");
		}

		screen->attrib = attrib;
	}

	if(x - from_x != 1 || from_y != y) {
		append_output("\x1b[%d;%dH", y + 1, x + 1);
	}

	append_output("%c", ch);

	from_x = x;
	from_y = y;

	screen->physical_buffer[y * screen->columns + x] = screen->buffer[y * screen->columns + x];
}
