#include "termmanip.h"
#include <stdio.h>
#include <stdarg.h>
#include <sys/select.h>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#else
#include <unistd.h>
#endif

int tm_win_input_ch(Tm_window* win) {
	int ret = 0;
	char ch = 0;

	tm_win_update(win);

#ifdef _WIN32
	if(WaitForSingleObject(GetStdHandle(STD_INPUT_HANDLE), win->input_amount) == WAIT_OBJECT_0) {
		DWORD bytes_read = 0;
		ReadConsole(GetStdHandle(STD_INPUT_HANDLE), &ch, 1, &bytes_read, NULL);
	}
#else
	fd_set input_set;

	FD_ZERO(&input_set);
	FD_SET(fileno(stdin), &input_set);

	struct timeval time;
	time.tv_usec = win->input_timeout * 1000;

	select(1, &input_set, NULL, NULL, &time);

	if(FD_ISSET(fileno(stdin), &input_set)) {
		read(fileno(stdin), &ch, 1);
	}
#endif

	if(win->flags & TM_FLAG_ECHO) {
		if((ret = tm_win_print(win, "%c", ch)) == TM_ERROR) {
			return ch;
		}

		tm_win_update(win);
	}


	return ch;
}

void tm_win_input_str(Tm_window* win, char* str, int max_size) { 
	int i = 0;
	int ch = 0;

	int og_flags = tm_win_get_flags(win);

	tm_win_flags(win, TM_FLAG_INPUTBLOCK | TM_FLAG_RAW | TM_FLAG_CURSOR_VISIBLE, 1);
	tm_win_flags(win, TM_FLAG_ECHO, 0);

	while(1) {
		ch = tm_win_input_ch(win);

		if(ch == '\n' || ch == '\r') {
			break;
		}

		if(ch == '\177' || ch == '\b') {
			if(i > 0) {
				str[i] = '\0';
				i--;
			}

			else {
				continue;
			}

			int tempX = tm_win_get_cursor_x(win);
			int tempY = tm_win_get_cursor_y(win);

			tm_win_cursor(win, tm_win_get_cursor_x(win) - 1, tm_win_get_cursor_y(win));
			tm_win_putch(win, tm_win_get_background(win).disp, tm_win_get_background(win).attrib);
			tm_win_cursor(win, tempX - 1, tempY);

			tm_win_update(win);

			continue;
		}

		if(tm_win_print(win, "%c", ch) != TM_ERROR) {
			if(i <= max_size) {
				str[i] = ch;
				i++;
			}

			tm_win_update(win);
		}
	}

	str[i] = '\0';

	tm_win_flags(win, TM_FLAG_ALL, 0);
	tm_win_flags(win, og_flags, 1);

	tm_win_print(win, "\n");
}

void tm_win_input(Tm_window* win, char* str, ...) {
	char new_str[4096];
	tm_win_input_str(win, new_str, 4096);

	va_list list;

	va_start(list, str);

	vsscanf(new_str, str, list);

	va_end(list);
}
