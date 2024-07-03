#include "termmanip.h"

int tm_return(Tm_terminal* terminal) {
	return terminal->tm_return_number;
}

void tm_set_return(Tm_terminal* terminal, int value) {
	terminal->tm_return_number = value;
}
