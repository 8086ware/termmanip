#include "termmanip.h"
#include <string.h>

void process_esc_input(Tm_input* input, char* escape_input) {
	if(strcmp(escape_input, "[A") == 0) {
		input->key = TM_KEY_UP;
	}

	if(strcmp(escape_input, "[B") == 0) {
		input->key = TM_KEY_DOWN;
	}

	if(strcmp(escape_input, "[C") == 0) {
		input->key = TM_KEY_RIGHT;
	}

	if(strcmp(escape_input, "[D") == 0) {
		input->key = TM_KEY_LEFT;
	}

	if(strcmp(escape_input, "[H") == 0) {
		input->key = TM_KEY_HOME;
	}

	if(strcmp(escape_input, "[F") == 0) {
		input->key = TM_KEY_END;
	}

	if(strcmp(escape_input, "OP") == 0) {
		input->key = TM_KEY_F1;
	}

	if(strcmp(escape_input, "OQ") == 0) {
		input->key = TM_KEY_F2;
	}

	if(strcmp(escape_input, "OR") == 0) {
		input->key = TM_KEY_F3;
	}

	if(strcmp(escape_input, "OS") == 0) {
		input->key = TM_KEY_F4;
	}

	if(strcmp(escape_input, "[15~") == 0) {
		input->key = TM_KEY_F5;
	}

	if(strcmp(escape_input, "[17~") == 0) {
		input->key = TM_KEY_F6;
	}

	if(strcmp(escape_input, "[18~") == 0) {
		input->key = TM_KEY_F7;
	}

	if(strcmp(escape_input, "[19~") == 0) {
		input->key = TM_KEY_F8;
	}

	if(strcmp(escape_input, "[20~") == 0) {
		input->key = TM_KEY_F9;
	}

	if(strcmp(escape_input, "[21~") == 0) {
		input->key = TM_KEY_F10;
	}

	if(strcmp(escape_input, "[23~") == 0) {
		input->key = TM_KEY_F11;
	}

	if(strcmp(escape_input, "[24~") == 0) {
		input->key = TM_KEY_F12;
	}

	if(strcmp(escape_input, "[2~") == 0) {
		input->key = TM_KEY_INSERT;
	}

	if(strcmp(escape_input, "[5~") == 0) {
		input->key = TM_KEY_PG_UP;
	}

	if(strcmp(escape_input, "[6~") == 0) {
		input->key = TM_KEY_PG_DOWN;
	}

	if(strcmp(escape_input, "[1;5A") == 0) {
		input->ctrl_down = 1;
		input->key = TM_KEY_UP;
	}

	if(strcmp(escape_input, "[1;5B") == 0) {
		input->ctrl_down = 1;
		input->key = TM_KEY_DOWN;
	}

	if(strcmp(escape_input, "[1;5C") == 0) {
		input->ctrl_down = 1;
		input->key = TM_KEY_RIGHT;
	}

	if(strcmp(escape_input, "[1;5D") == 0) {
		input->ctrl_down = 1;
		input->key = TM_KEY_LEFT;
	}
}
