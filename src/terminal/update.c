#include "termmanip.h"
#include "terminal.h"
#include <stdlib.h>
#include <stdio.h>
#include "return.h"
#include <memory.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <poll.h>
#include <unistd.h>
#endif

int tm_terminal_update(Tm_terminal* terminal) {
#ifdef _WIN32
	INPUT_RECORD input;
	DWORD bytes_read;
	PeekConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &input, 1, &bytes_read);

	if (bytes_read > 0 && input.EventType == WINDOW_BUFFER_SIZE_EVENT) {
		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &input, 1, &bytes_read);
		terminal_resize(terminal);
		terminal->resized = 1;
	}
#else
	struct pollfd signal_poll;
	signal_poll.fd = terminal->signal_fd;
	signal_poll.events = POLLIN;

	poll(&signal_poll, 1, 0);

	if (signal_poll.revents & POLLIN) {
		char buf[1024];
		read(terminal->signal_fd, &buf, 1024);
		terminal_resize(terminal);
		terminal->resized = 1;
	}
#endif

	for(int i = 0; i < terminal->columns * terminal->rows; i++) {
		terminal_write(terminal, i, 0, ' ', 0);
	}

	int parent_x = 0;
	int parent_y = 0;

	Tm_window* parent = NULL;

	for(int i = 0; i < terminal->window_amount; i++) {
		if(terminal->windows[i]->update) {
			parent = terminal->windows[i]->parent;

			while (parent != NULL) {
				parent_x += parent->position_x;
				parent_y += parent->position_y;

				parent = parent->parent;
			}

			Tm_char* temp_physical_window_buffer = terminal->windows[i]->physical_window->buffer;

			memcpy(terminal->windows[i]->physical_window, terminal->windows[i], sizeof(Tm_window));
			terminal->windows[i]->physical_window->physical_window = NULL;

			terminal->windows[i]->physical_window->buffer = realloc(temp_physical_window_buffer, sizeof(Tm_char) * terminal->windows[i]->buffer_columns * terminal->windows[i]->buffer_rows);

			if (terminal->windows[i]->physical_window->buffer == NULL) {
				tm_set_return(terminal, TM_OUT_OF_MEM);
				return TM_ERROR;
			}

			memcpy(terminal->windows[i]->physical_window->buffer, terminal->windows[i]->buffer, sizeof(Tm_char) * terminal->windows[i]->buffer_columns * terminal->windows[i]->buffer_rows);
			terminal->windows[i]->update = 0;
		}

		else {
			parent = terminal->windows[i]->physical_window->parent;

			while (parent != NULL) {
				parent_x += parent->position_x;
				parent_y += parent->position_y;

				parent = parent->parent;
			}
		}
		
		terminal_write_win_to_terminal(terminal->windows[i]->physical_window, parent_x, parent_y);
		
		parent_x = 0;
		parent_y = 0;
	}

	parent = terminal->last_updated_window->parent;

	while(parent != NULL) {	
		parent_x += parent->position_x;
		parent_y += parent->position_y;

		parent = parent->parent;
	}

	if (terminal->last_updated_window->flags & TM_FLAG_CURSOR_VISIBLE && (terminal->flags & TM_FLAG_CURSOR_VISIBLE) == 0) {
		terminal_append_output(terminal, "\x1b[?25h");
	}

	else if ((terminal->last_updated_window->flags & TM_FLAG_CURSOR_VISIBLE) == 0 && terminal->flags & TM_FLAG_CURSOR_VISIBLE) {
		terminal_append_output(terminal, "\x1b[?25l");
	}

	if (terminal->last_updated_window->flags & TM_FLAG_MOUSE_INPUT && (terminal->flags & TM_FLAG_MOUSE_INPUT) == 0) {
		terminal_append_output(terminal, "\x1b[?1003h\x1b[?1006h");
	}

	else if ((terminal->last_updated_window->flags & TM_FLAG_MOUSE_INPUT) == 0 && terminal->flags & TM_FLAG_MOUSE_INPUT) {
		terminal_append_output(terminal, "\x1b[?1003l\x1b[?1006l");
	}

	terminal->flags = terminal->last_updated_window->flags;

	terminal->cursor_x = terminal->last_updated_window->cursor_x - terminal->last_updated_window->buffer_position_x + terminal->last_updated_window->position_x + parent_x;
	terminal->cursor_y = terminal->last_updated_window->cursor_y - terminal->last_updated_window->buffer_position_y + terminal->last_updated_window->position_y + parent_y + terminal->last_updated_window->wrapped_lines;

	terminal_make_output(terminal);

	// Is the actual cursor on the terminal screen (the last written character) matching to the inner structure terminal cursor
	if(terminal->last_updated_x + 1 != terminal->cursor_x || terminal->last_updated_y != terminal->cursor_y) {
		terminal_append_output(terminal, "\x1b[%d;%dH", terminal->cursor_y + 1, terminal->cursor_x + 1);

		terminal->last_updated_x = terminal->cursor_x - 1;
		terminal->last_updated_y = terminal->cursor_y;
	}

	write(fileno(stdout), terminal->output, terminal->output_len);

	free(terminal->output);
	terminal->output_len = 0;
	terminal->output = NULL;

	memcpy(terminal->physical_buffer, terminal->buffer, sizeof(Tm_char) * terminal->columns * terminal->rows);
	return 0;
}

