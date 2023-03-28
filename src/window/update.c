#include "termmanip.h"
#include <unistd.h>
#include <stdio.h>
#include "append_output.h"
#include <stdlib.h>
#include "pending_change.h"

#ifdef _WIN32
#include <windows.h>
#endif

void terminal_move_cursor(int x, int y) {
	if(y != screen->cursor_y) {
		append_output("\x1b[%d;%dH", y + 1, x + 1);
		return;
	}

	if(x - screen->cursor_x == 1) {
		return;
	}

	if(x - screen->cursor_x < 8 && x - screen->cursor_x > 1) {
		for(int i = 1; i < x - screen->cursor_x; i++) {
			append_output(" ");
		}
	}

	else {
		append_output("\x1b[%d;%dH", y + 1, x + 1);
	}
}

void tm_screen_update() {
	for(int i = 0; i < screen->pending_change_amount; i++) {	
		terminal_move_cursor(screen->pending_changes[i].x, screen->pending_changes[i].y);

		char disp = screen->pending_changes[i].tm_char.disp;
		uint32_t attrib = screen->pending_changes[i].tm_char.attrib;

		if(screen->attrib != attrib) {
			screen->attrib = attrib;

			if(attrib & TM_ATTRIB_BOLD) {
				append_output("\x1b[1m");
			}

			if(attrib & TM_ATTRIB_DIM) {
				append_output("\x1b[2m");
			}

			if(attrib & TM_ATTRIB_ITALIC) {
				append_output("\x1b[3m");
			}

			if(attrib & TM_ATTRIB_UNDERLINE) {
				append_output("\x1b[4m");
			}

			if(attrib & TM_ATTRIB_BLINKING) {
				append_output("\x1b[5m");
			}

			if(attrib & TM_ATTRIB_HIGHLIGHT) {
				append_output("\x1b[7m");
			}

			if(attrib & TM_ATTRIB_HIDDEN) {
				append_output("\x1b[8m");
			}

			if(attrib & TM_ATTRIB_STRIKE) {
				append_output("\x1b[9m");
			}

			if((attrib & TM_ATTRIB_FG_MASK) != 0) {
				append_output("\x1b[%dm", (attrib & TM_ATTRIB_FG_MASK) >> 16);
			}

			if((attrib & TM_ATTRIB_BG_MASK) != 0) {
				append_output("\x1b[%dm", (attrib & TM_ATTRIB_BG_MASK) >> 24);
			}

			if(attrib & TM_ATTRIB_RESET) {
				append_output("\x1b[0m");
			}
		}

		if(disp == '\0') {
			disp = ' ';
		}

		append_output("%c", disp);

		screen->cursor_x = screen->pending_changes[i].x;
		screen->cursor_y = screen->pending_changes[i].y;
	}

#ifdef _WIN32
	DWORD bytes_written = 0;
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), screen->output, screen->output_len, &bytes_written, NULL);
#else
	write(fileno(stdout), screen->output, screen->output_len);
#endif

	free(screen->output);
	screen->output = NULL;
	screen->output_len = 0;

	tm_free_pending_changes();
}

void tm_win_write_to_screen(Tm_window* win) {
	int parent_x = 0;
	int parent_y = 0;

	if(win->parent != NULL) {
		parent_x = win->parent->position_x;
		parent_y = win->parent->position_y;
	}

	for(int i = 0; i < win->columns * win->rows; i++) {
		char disp = win->buffer[i].disp;
		uint32_t attrib = win->buffer[i].attrib;

		char physical_disp = win->physical_buffer[i].disp;
		uint32_t physical_attrib = win->physical_buffer[i].attrib;

		if(physical_disp != disp || physical_attrib != attrib) {
			tm_add_pending_change(win->buffer[i], win->position_x + parent_x + i % win->columns, parent_y + win->position_y + i / win->columns);
		}
	}

	for(int i = 0; i < win->columns * win->rows; i++) {
		win->physical_buffer[i] = win->buffer[i];
	}

	for(int i = 0; i < win->children_amount; i++) {
		tm_win_write_to_screen(win->children[i]);
	}
}

void tm_win_update(Tm_window* win) {
	tm_win_write_to_screen(win);
	tm_screen_update();
}
