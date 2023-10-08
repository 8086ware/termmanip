#include "termmanip.h"
#include <string.h>

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

	else {
		input->key = *escape_input;
		input->alt_down = 1;
	}
}
