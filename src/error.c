#include "termmanip.h"
#include "error.h"

int tm_error_number = 0;

int tm_error() {
	return tm_error_number;
}

void tm_set_error(int value) {
	tm_error_number = value;
}
