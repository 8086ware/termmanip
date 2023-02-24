#include "termmanip.h"
#include <unistd.h>
#include <stdio.h>

char tm_input_ch() {
	char ch;
	read(fileno(stdin), &ch, 1);
	return ch;
}
