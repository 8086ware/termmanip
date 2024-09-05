#include "termmanip.h"

void tm_win_child_select(Tm_window* win, Tm_input* input) {
	if(win->children_amount == 0)
		return;

	if(win->child_type != TM_CHILD_NORMAL) {
		if(input->key == TM_KEY_RIGHT) {
			if(win->selected_child_window_id + 1 < win->children_amount) {
				tm_win_background(win->selected_child_window, win->selected_child_window->background_tm_char.disp, win->selected_child_window->background_tm_char.attrib & ~TM_ATTRIB_HIGHLIGHT);
				win->selected_child_window = win->children[win->selected_child_window_id + 1];
				win->selected_child_window_id++;
			}
		}

		else if(input->key == TM_KEY_LEFT) {
			if(win->selected_child_window_id - 1 >= 0) {
				tm_win_background(win->selected_child_window, win->selected_child_window->background_tm_char.disp, win->selected_child_window->background_tm_char.attrib & ~TM_ATTRIB_HIGHLIGHT);
				win->selected_child_window = win->children[win->selected_child_window_id - 1];
				win->selected_child_window_id--;
			}
		}
	}

	tm_win_background(win->selected_child_window, win->selected_child_window->background_tm_char.disp, win->selected_child_window->background_tm_char.attrib | TM_ATTRIB_HIGHLIGHT);

	switch(win->selected_child_window->child_type) {
		case TM_CHILD_BUTTON:
			if(input->ctrl_character == TM_KEY_CR || input->ctrl_character == TM_KEY_LF) {
				input->child_window_selected = 1;
			}
			break;
		default:
			break;
	}
}
