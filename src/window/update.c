#include "termmanip.h"
#include <unistd.h>
#include <stdio.h>
#include "append_output.h"
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#endif

typedef struct Pending_Change {
	int x;
	int y;

	Tm_char* changed_xy;
	_Bool move;
} Pending_Change;

void tm_win_update(Tm_window* win) {
	int parent_x = 0;
	int parent_y = 0;

	if(win->parent != NULL) {
		parent_x = win->parent->position_x;
		parent_y = win->parent->position_y;			
	}

	static uint32_t last_attrib;
	_Bool found = 0;

	int pending_changes_amount = 0;

	for(int y = 0; y < win->rows; y++) {
		for(int x = 0; x < win->columns; x++) {
			char phys_disp = win->physical_buffer[y * win->columns + x].disp;
			char disp = win->buffer[y * win->columns + x].disp;
			uint32_t phys_attrib = win->physical_buffer[y * win->columns + x].attrib;
			uint32_t attrib = win->buffer[y * win->columns + x].attrib;

			if(phys_disp != disp || phys_attrib != attrib) {
				found = 1;
				pending_changes_amount++;
			}
		}
	}

	Pending_Change* pending_changes = malloc(sizeof(Pending_Change) * pending_changes_amount);

	int i = 0;
	for(int y = 0; y < win->rows; y++) {
		for(int x = 0; x < win->columns; x++) {
			char phys_disp = win->physical_buffer[y * win->columns + x].disp;
			char disp = win->buffer[y * win->columns + x].disp;
			uint32_t phys_attrib = win->physical_buffer[y * win->columns + x].attrib;
			uint32_t attrib = win->buffer[y * win->columns + x].attrib;

			if(phys_disp != disp || phys_attrib != attrib) {
				pending_changes[i].changed_xy = &win->buffer[y * win->columns + x];
				pending_changes[i].x = x;
				pending_changes[i].y = y;
				pending_changes[i].move = 0;

				if(i > 0) {
					if(pending_changes[i].y > pending_changes[i - 1].y) {
						pending_changes[i].move = 1;
					}

					if((pending_changes[i].x - pending_changes[i - 1].x) > 5) {
						pending_changes[i].move = 1;
					}
				}

				i++;
			}
		}
	}

	append_output(win, "\x1b[%d;%dH", pending_changes[0].y + win->position_y + 1 + parent_y, win->position_x + pending_changes[0].x + 1 + parent_x);

	for(int i = 0; i < pending_changes_amount; i++) {
		uint32_t attrib = pending_changes[i].changed_xy->attrib;
		char disp = pending_changes[i].changed_xy->disp;

		if(pending_changes[i].move) {
			append_output(win, "\x1b[%d;%dH", pending_changes[i].y + win->position_y + 1 + parent_y, win->position_x + pending_changes[i].x + 1 + parent_x);
		}

		if(last_attrib != attrib) {
			last_attrib = attrib;

			if(attrib & TM_ATTRIB_BOLD) {
				append_output(win, "\x1b[1m");
			}

			if(attrib & TM_ATTRIB_DIM) {
				append_output(win, "\x1b[2m");
			}

			if(attrib & TM_ATTRIB_ITALIC) {
				append_output(win, "\x1b[3m");
			}

			if(attrib & TM_ATTRIB_UNDERLINE) {
				append_output(win, "\x1b[4m");
			}

			if(attrib & TM_ATTRIB_BLINKING) {
				append_output(win, "\x1b[5m");
			}

			if(attrib & TM_ATTRIB_HIGHLIGHT) {
				append_output(win, "\x1b[7m");
			}

			if(attrib & TM_ATTRIB_HIDDEN) {
				append_output(win, "\x1b[8m");
			}

			if(attrib & TM_ATTRIB_STRIKE) {
				append_output(win, "\x1b[9m");
			}

			if(attrib & TM_ATTRIB_ALTERNATE) {
				append_output(win, "\x1b(0");
			}

			if(attrib & TM_ATTRIB_MAIN) {
				append_output(win, "\x1b(B");
			}

			if((attrib & TM_ATTRIB_FG_MASK) != 0) {
				append_output(win, "\x1b[%dm", (attrib & TM_ATTRIB_FG_MASK) >> 16);
			}

			if((attrib & TM_ATTRIB_BG_MASK) != 0) {
				append_output(win, "\x1b[%dm", (attrib & TM_ATTRIB_BG_MASK) >> 24);
			}

			if(attrib & TM_ATTRIB_RESET) {
				append_output(win, "\x1b[0m");
			}
		}

		if(disp == '\0') {
			disp = ' ';
		}

		append_output(win, "%c", disp);
	}

	free(pending_changes);

	if(win->cursor_moved) {
		append_output(win, "\x1b[%d;%dH", win->cursor_y + win->position_y + 1 + parent_y, win->position_x + win->cursor_x + 1 + parent_x);
		win->cursor_moved = 0;
	}

	if(found) {
#ifdef _WIN32
		DWORD bytes_written = 0;
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), win->output, win->output_len, &bytes_written, NULL);
#else
		write(fileno(stdout), win->output, win->output_len);
#endif
	}

	free(win->output);
	win->output = NULL;
	win->output_len = 0;

	for(int i = 0; i < win->columns * win->rows; i++) {
		win->physical_buffer[i].disp = win->buffer[i].disp;
		win->physical_buffer[i].attrib = win->buffer[i].attrib;
	}

	for(int i = 0; i < win->children_amount; i++) {
		tm_win_update(win->children[i]);
	}
}
