#include "process_esc_input.h"
#include <string.h>
#include <stdio.h>

void process_esc_input(Tm_input* input, char* escape_input) {
	int len = strlen(escape_input);

	for(int i = 0; i < len; i++) {
		if(escape_input[i] == '\x1b') {
			escape_input[i] = '\0';
			break;
		}
	}

	char c1, c2, c3, c4, c5;

	c1 = escape_input[0];
	c2 = escape_input[1];
	c3 = escape_input[2];
	c4 = escape_input[3];
	c5 = escape_input[4];

	if(c1 == '[' && c2 == '<') {
		int mouse_type = 0;
		int x = 0;
		int y = 0;
		
		char up_or_down = 0;

		sscanf(escape_input, "[<%d;%d;%d%c", &mouse_type, &x, &y, &up_or_down);
	
		x--;
		y--;

		if(up_or_down == 'M') {
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

	if(c1 == '[') {
		if((c2 == '1' && c3 == ';') || ((c2 == '2' || c2 == '1') && c4 == ';') || (c2 >= '2' && c2 <= '8')) {
			if(c2 == '1' && c3 == ';') {
				c2 = c5;
			}

			if(c4 == '2' || c5 == '2') {
				input->shift_down = 1;
			}

			else if(c4 == '3' || c5 == '3') {
				input->alt_down = 1;
			}

			else if(c4 == '4' || c5 == '4') {
				input->alt_down = 1;
				input->shift_down = 1;
			}

			else if(c4 == '5' || c5 == '5') {
				input->ctrl_down = 1;
			}

			else if(c4 == '6' || c5 == '6') {
				input->ctrl_down = 1;
				input->shift_down = 1;
			}

			else if(c4 == '7' || c5 == '7') {
				input->ctrl_down = 1;
				input->alt_down = 1;
			}

			else if(c4 == '8' || c5 == '8') {
				input->ctrl_down = 1;
				input->alt_down = 1;
				input->shift_down = 1;
			}
		}

		if(c2 == '1') {
			if(c3 == '5') {
				input->key = TM_KEY_F5;
			}
			else if(c3 == '7') {
				input->key = TM_KEY_F6;
			}
			else if(c3 == '8') {
				input->key = TM_KEY_F7;
			}
			else if(c3 == '9') {
				input->key = TM_KEY_F8;
			}
		}

		else if(c2 == '2') {
			if(c3 == '0') {
				input->key = TM_KEY_F9;
			}

			else if(c3 == '1') {
				input->key = TM_KEY_F10;
			}

			else if(c3 == '3') {
				input->key = TM_KEY_F11;
			}

			else if(c3 == '4') {
				input->key = TM_KEY_F12;
			}
		}

		else if(c2 == 'A') {
			input->key = TM_KEY_UP;
		}

		else if(c2 == 'B') {
			input->key = TM_KEY_DOWN;
		}

		else if(c2 == 'C') {
			input->key = TM_KEY_RIGHT;
		}

		else if(c2 == 'D') {
			input->key = TM_KEY_LEFT;
		}

		else if(c2 == 'H') {
			input->key = TM_KEY_HOME;
		}

		else if(c2 == 'F') {
			input->key = TM_KEY_END;
		}


		if(c3 == '~' || c3 == ';') {
			if(c2 == '2') {
				input->key = TM_KEY_INSERT;
			}

			else if(c2 == '3') {
				input->key = TM_KEY_DELETE;
			}

			else if(c2 == '5') {
				input->key = TM_KEY_PG_UP;
			}

			else if(c2 == '6') {
				input->key = TM_KEY_PG_DOWN;
			}
		}
	}

	else if(c1 == 'O') {
		if(c2 == 'P') {
			input->key = TM_KEY_F1;
		}

		else if(c2 == 'Q') {
			input->key = TM_KEY_F2;
		}

		else if(c2 == 'R') {
			input->key = TM_KEY_F3;
		}

		else if(c2 == 'S') {
			input->key = TM_KEY_F4;
		}
	}

	else {
		input->key = c1;
		input->alt_down = 1;
	}
}
