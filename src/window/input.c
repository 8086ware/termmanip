#include "termmanip.h"
#include <unistd.h>
#include <stdio.h>
#include "append_win.h"

int tm_win_input_ch(Tm_window* win) {
	int ret = 0;
	char ch[4096];

	if(win->flags & ~TM_FLAG_RAW) {
		if((ret = tm_win_input_str(win, ch, 4096)) == TM_ERROR) {
			return ret;
		}
	}

	else {
		read(fileno(stdin), ch, 1);
	}

	return *ch;
}

void tm_win_input_str(Tm_window* win, char* str, int max_size) {
	int i = 0;
	char ch = 0;

	while(i != max_size && ch != '\n') {
		ch = tm_input_ch();
		tm_win_print(win, "%c", ch);
		tm_win_update(win);
		str[i] = ch;
		i++;
	}

	str[i] = '\0';
}
