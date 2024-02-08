#include "termmanip.h"

int tm_return_number = 0;

int tm_return() {
	return tm_return_number;
}

void tm_set_return(int value) {
	tm_return_number = value;
}
