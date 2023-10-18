#include "process_esc_input.h"
#include <string.h>
#include <stdio.h>

void process_esc_input(Tm_input* input, char* escape_input) {
	if(strcmp(escape_input, "[A") == 0) {
		input->key = TM_KEY_UP;
	}

	else if(strcmp(escape_input, "[B") == 0) {
		input->key = TM_KEY_DOWN;
	}

	else if(strcmp(escape_input, "[C") == 0) {
		input->key = TM_KEY_RIGHT;
	}

	else if(strcmp(escape_input, "[D") == 0) {
		input->key = TM_KEY_LEFT;
	}

	else if(strcmp(escape_input, "[H") == 0) {
		input->key = TM_KEY_HOME;
	}

	else if(strcmp(escape_input, "[F") == 0) {
		input->key = TM_KEY_END;
	}

	else if(strcmp(escape_input, "OP") == 0) {
		input->key = TM_KEY_F1;
	}

	else if(strcmp(escape_input, "OQ") == 0) {
		input->key = TM_KEY_F2;
	}

	else if(strcmp(escape_input, "OR") == 0) {
		input->key = TM_KEY_F3;
	}

	else if(strcmp(escape_input, "OS") == 0) {
		input->key = TM_KEY_F4;
	}

	else if(strcmp(escape_input, "[15~") == 0) {
		input->key = TM_KEY_F5;
	}

	else if(strcmp(escape_input, "[17~") == 0) {
		input->key = TM_KEY_F6;
	}

	else if(strcmp(escape_input, "[18~") == 0) {
		input->key = TM_KEY_F7;
	}

	else if(strcmp(escape_input, "[19~") == 0) {
		input->key = TM_KEY_F8;
	}

	else if(strcmp(escape_input, "[20~") == 0) {
		input->key = TM_KEY_F9;
	}

	else if(strcmp(escape_input, "[21~") == 0) {
		input->key = TM_KEY_F10;
	}

	else if(strcmp(escape_input, "[23~") == 0) {
		input->key = TM_KEY_F11;
	}

	else if(strcmp(escape_input, "[24~") == 0) {
		input->key = TM_KEY_F12;
	}

	else if(strcmp(escape_input, "[2~") == 0) {
		input->key = TM_KEY_INSERT;
	}

	else if(strcmp(escape_input, "[5~") == 0) {
		input->key = TM_KEY_PG_UP;
	}

	else if(strcmp(escape_input, "[6~") == 0) {
		input->key = TM_KEY_PG_DOWN;
	}

	else if(strcmp(escape_input, "[1;5A") == 0) {
		input->ctrl_down = 1;
		input->key = TM_KEY_UP;
	}

	else if(strcmp(escape_input, "[1;5B") == 0) {
		input->ctrl_down = 1;
		input->key = TM_KEY_DOWN;
	}

	else if(strcmp(escape_input, "[1;5C") == 0) {
		input->ctrl_down = 1;
		input->key = TM_KEY_RIGHT;
	}

	else if(strcmp(escape_input, "[1;5D") == 0) {
		input->ctrl_down = 1;
		input->key = TM_KEY_LEFT;
	}

	else if(strcmp(escape_input, "[1;5D") == 0) {
		input->ctrl_down = 1;
		input->key = TM_KEY_LEFT;
	}
	
	else if(*escape_input == '[' && *(escape_input + 1) == '<') {
		escape_input += 2;
		
		int mouse_type = 0;
		int x = 0;
		int y = 0;
		
		char up_or_down = 0;

		sscanf(escape_input, "%d;%d;%d%c", &mouse_type, &x, &y, &up_or_down);
	
		x--;
		y--;

		if(up_or_down == 'm') {
			input->mouse_up = 1;
		}
	
		else if(up_or_down == 'M') {
			input->mouse_down = 1;
		}

		if(mouse_type == 35 || mouse_type == 43 || mouse_type == 51 || mouse_type == 59) {
			input->mouse_moved = 1;
		}

		if(mouse_type == 0 || mouse_type == 32 || mouse_type == 8 || mouse_type == 40 || mouse_type == 16 || mouse_type == 48 || mouse_type == 24 || mouse_type == 56) {
			input->mouse_left = 1;
		}

		if(mouse_type == 1 || mouse_type == 33 || mouse_type == 9 || mouse_type == 41 || mouse_type == 17 || mouse_type == 49 || mouse_type == 25 || mouse_type == 57) {
			input->mouse_middle = 1;
		}

		if(mouse_type == 2 || mouse_type == 34 || mouse_type == 10 || mouse_type == 42 || mouse_type == 18 || mouse_type == 50 || mouse_type == 26 || mouse_type == 58) {
			input->mouse_right = 1;
		}

		if(mouse_type == 64 || mouse_type == 72 || mouse_type == 80 || mouse_type == 88) {
			input->scroll_up = 1;
		}

		if(mouse_type == 65 || mouse_type == 73 || mouse_type == 81 || mouse_type == 89) {
			input->scroll_down = 1;
		}

		if(mouse_type == 16 || mouse_type == 17 || mouse_type == 18 || mouse_type == 48 || mouse_type == 49 || mouse_type == 50 || mouse_type == 51 || mouse_type == 80 || mouse_type == 81) {
			input->ctrl_down = 1;
		}

		if(mouse_type == 8 || mouse_type == 9 || mouse_type == 10 || mouse_type == 40 || mouse_type == 41 || mouse_type == 42 || mouse_type == 43 || mouse_type == 72 || mouse_type == 73) {
			input->alt_down = 1;
		}

		if(mouse_type == 24 || mouse_type == 25 || mouse_type == 26 || mouse_type == 56 || mouse_type == 57 || mouse_type == 58 || mouse_type == 59 || mouse_type == 88 || mouse_type == 89) {
			input->ctrl_down = 1;
			input->alt_down = 1;
		}

		input->mouse_x = x;
		input->mouse_y = y;
	}

	else {
		input->key = *escape_input;
		input->alt_down = 1;
	}
}
