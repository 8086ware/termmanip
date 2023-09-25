#include "termmanip.h"
#include "screen.h"

void screen_output_write(int x, int y, char ch, uint32_t attrib) {
	if(screen->attrib != attrib) {
		if(attrib & TM_ATTRIB_ALTERNATE && (screen->attrib & TM_ATTRIB_ALTERNATE) == 0) {
			screen_append_output("\x1b(0");
		}

		else if((attrib & TM_ATTRIB_ALTERNATE) == 0 && screen->attrib & TM_ATTRIB_ALTERNATE) {
			screen_append_output("\x1b(B");
		}

		if(attrib & TM_ATTRIB_BOLD && (screen->attrib & TM_ATTRIB_BOLD) == 0) {
			screen_append_output("\x1b[1m");
		}

		else if((attrib & TM_ATTRIB_BOLD) == 0 && screen->attrib & TM_ATTRIB_BOLD) {
			screen_append_output("\x1b[22m");
		}

		if(attrib & TM_ATTRIB_DIM && (screen->attrib & TM_ATTRIB_DIM) == 0) {
			screen_append_output("\x1b[2m");
		}

		else if((attrib & TM_ATTRIB_DIM) == 0 && screen->attrib & TM_ATTRIB_DIM) {
			screen_append_output("\x1b[22m");
		}

		if(attrib & TM_ATTRIB_ITALIC && (screen->attrib & TM_ATTRIB_ITALIC) == 0) {
			screen_append_output("\x1b[3m");
		}

		else if((attrib & TM_ATTRIB_ITALIC) == 0 && screen->attrib & TM_ATTRIB_ITALIC) {
			screen_append_output("\x1b[23m");
		}

		if(attrib & TM_ATTRIB_UNDERLINE && (screen->attrib & TM_ATTRIB_UNDERLINE) == 0) {
			screen_append_output("\x1b[4m");
		}

		else if((attrib & ~TM_ATTRIB_UNDERLINE) == 0 && screen->attrib & TM_ATTRIB_UNDERLINE) {
			screen_append_output("\x1b[24m");
		}

		if(attrib & TM_ATTRIB_BLINKING && (screen->attrib & TM_ATTRIB_BLINKING) == 0) {
			screen_append_output("\x1b[5m");
		}

		else if((attrib & TM_ATTRIB_BLINKING) == 0 && screen->attrib & TM_ATTRIB_BLINKING) {
			screen_append_output("\x1b[25m");
		}

		if(attrib & TM_ATTRIB_HIGHLIGHT && (screen->attrib & TM_ATTRIB_HIGHLIGHT) == 0) {
			screen_append_output("\x1b[7m");
		}

		else if((attrib & TM_ATTRIB_HIGHLIGHT) == 0 && screen->attrib & TM_ATTRIB_HIGHLIGHT) {
			screen_append_output("\x1b[27m");
		}

		if(attrib & TM_ATTRIB_HIDDEN && (screen->attrib & TM_ATTRIB_HIDDEN) == 0) {
			screen_append_output("\x1b[8m");
		}

		else if((attrib & TM_ATTRIB_HIDDEN) == 0 && screen->attrib & TM_ATTRIB_HIDDEN) {
			screen_append_output("\x1b[28m");
		}

		if(attrib & TM_ATTRIB_STRIKE && (screen->attrib & TM_ATTRIB_STRIKE) == 0) {
			screen_append_output("\x1b[9m");
		}

		else if((attrib & TM_ATTRIB_STRIKE) == 0 && screen->attrib & TM_ATTRIB_STRIKE) {
			screen_append_output("\x1b[29m");
		}

		if(attrib & TM_ATTRIB_FG_MASK && (screen->attrib & TM_ATTRIB_FG_MASK) != (attrib & TM_ATTRIB_FG_MASK)) {
			screen_append_output("\x1b[%dm", (attrib & TM_ATTRIB_FG_MASK) >> 16);
		}

		else if((attrib & TM_ATTRIB_FG_MASK) == 0 && (screen->attrib & TM_ATTRIB_FG_MASK) != 0) {
			screen_append_output("\x1b[39m");
		}

		if(attrib & TM_ATTRIB_BG_MASK && (screen->attrib & TM_ATTRIB_BG_MASK) != (attrib & TM_ATTRIB_BG_MASK)) {
			screen_append_output("\x1b[%dm", (attrib & TM_ATTRIB_BG_MASK) >> 24);
		}

		else if((attrib & TM_ATTRIB_BG_MASK) == 0 && (screen->attrib & TM_ATTRIB_BG_MASK) != 0) {
			screen_append_output("\x1b[49m");
		}

		screen->attrib = attrib;
	}

	if(x - screen->last_updated_x != 1 || screen->last_updated_y != y) {
		screen_append_output("\x1b[%d;%dH", y + 1, x + 1);
	}

	screen_append_output("%c", ch);

	screen->last_updated_x = x;
	screen->last_updated_y = y;
}

