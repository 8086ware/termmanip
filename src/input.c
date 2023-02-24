#include "termmanip.h"
#include <unistd.h>
#include <stdio.h>

char tm_input_ch() {
	char ch;
	read(fileno(stdin), &ch, 1);
	return ch;
}

void tm_win_input_str(Tm_window* win, char* str, int max_size) {
	int i = 0;
	char ch = 0;

	while(i != max_size && ch != '\n') {
		ch = tm_input_ch();
		tm_win_print_ch(win, ch);
		tm_win_update(win);
		str[i] = ch;
		i++;
	}
}
