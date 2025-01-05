#include "termmanip.h"
#include "terminal.h"
#include <stdlib.h>

int terminal_win_select(Tm_terminal* terminal, Tm_input* input) {
	int prev_selected_window_id = terminal->selected_window_id;

	input->win_selected = NULL;
	_Bool changed_window = 0;

	if (input->key == TM_KEY_LEFT) {
		if (terminal->selected_window_id == -1) {
			for (int i = 0; i < terminal->window_amount; i++) {
				if (terminal->windows[i]->selectable) {
					terminal->selected_window_id = i;
				}
			}
		}

		if (terminal->selected_window_id > 0) {
			terminal->selected_window_id--;
			while (!terminal->windows[terminal->selected_window_id]->selectable) {
				if (terminal->selected_window_id > 0) {
					terminal->selected_window_id--;
				}

				else {
					terminal->selected_window_id = prev_selected_window_id;
					break;
				}
			}

			changed_window = 1;
		}
	}

	if (input->key == TM_KEY_RIGHT) {
		if (terminal->selected_window_id == -1) {
			for (int i = 0; i < terminal->window_amount; i++) {
				if (terminal->windows[i]->selectable) {
					terminal->selected_window_id = i;
				}
			}
		}

		if (terminal->selected_window_id < terminal->window_amount - 1) {
			terminal->selected_window_id++;
			while (!terminal->windows[terminal->selected_window_id]->selectable) {
				if (terminal->selected_window_id < terminal->window_amount - 1) {
					terminal->selected_window_id++;
				}

				else {
					terminal->selected_window_id = prev_selected_window_id;
					break;
				}
			}

			changed_window = 1;
		}
	}

	_Bool mouse_on_window = 0;

	if (terminal->flags & TM_FLAG_MOUSE_INPUT) {
		for (int i = terminal->window_amount - 1; i > 0; i--) {
			int parent_x = 0;
			int parent_y = 0;

			Tm_window* parent = terminal->windows[i]->parent;

			while (parent != NULL) {
				parent_x += parent->position_x;
				parent_y += parent->position_y;

				parent = parent->parent;
			}

			if (input->mouse_x >= terminal->windows[i]->position_x + parent_x && input->mouse_y >= terminal->windows[i]->position_y + parent_y && input->mouse_x < terminal->windows[i]->position_x + terminal->windows[i]->columns + parent_x && input->mouse_y < terminal->windows[i]->position_y + terminal->windows[i]->rows + parent_y) {
				if (terminal->windows[i]->selectable) {
					terminal->selected_window_id = i;
					
					if (terminal->selected_window_id != prev_selected_window_id) {
						changed_window = 1;
					}

					mouse_on_window = 1;
				}

				break;
			}
		}
	}

	if (changed_window) {
		if (prev_selected_window_id != -1) {
			tm_win_background(terminal->windows[prev_selected_window_id], terminal->windows[terminal->selected_window_id]->background_tm_char.disp, terminal->windows[prev_selected_window_id]->background_tm_char.attrib & ~TM_ATTRIB_HIGHLIGHT);
		}

		tm_win_background(terminal->windows[terminal->selected_window_id], terminal->windows[terminal->selected_window_id]->background_tm_char.disp, terminal->windows[terminal->selected_window_id]->background_tm_char.attrib | TM_ATTRIB_HIGHLIGHT);
	}

	if (!mouse_on_window && input->mouse_moved) {
		if (terminal->selected_window_id != -1) {
			tm_win_background(terminal->windows[prev_selected_window_id], terminal->windows[terminal->selected_window_id]->background_tm_char.disp, terminal->windows[prev_selected_window_id]->background_tm_char.attrib & ~TM_ATTRIB_HIGHLIGHT);
			terminal->selected_window_id = -1;
		}
	}

	int finished = 0;

	if (input->ctrl_character == TM_KEY_LF || input->ctrl_character == TM_KEY_CR || (!input->mouse_down && input->mouse_left)) {
		if (terminal->selected_window_id != -1) {
			input->win_selected = terminal->windows[terminal->selected_window_id];

			if (terminal->windows[terminal->selected_window_id]->parent->type == TM_WIN_DIALOG) {
				tm_win_free(terminal->windows[terminal->selected_window_id]->parent);
				terminal->selected_window_id = -1;
			}

			finished = 1;
		}
	}

	return finished;
}
