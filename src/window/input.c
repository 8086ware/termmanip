#include "termmanip.h"
#include <stdio.h>
#include <stdarg.h>
#include "screen.h"

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#else
#include <poll.h>
#include <unistd.h>
#endif

Tmkey_T tm_win_input_ch(Tm_window* win) {
	Tmkey_T ch = 0;

	tm_win_update(win);

#ifdef _WIN32
	INPUT_RECORD buffer;
	_Bool read = 0;
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	do {
		if(WaitForSingleObject(GetStdHandle(STD_INPUT_HANDLE), win->input_timeout) == WAIT_OBJECT_0) {
			DWORD bytes_read;
			ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &buffer, 1, &bytes_read);

			if(buffer.EventType == KEY_EVENT) {
				if(buffer.Event.KeyEvent.bKeyDown == TRUE) {
					ch = buffer.Event.KeyEvent.uChar.AsciiChar;
					read = 1;
				}
			}

			else if(buffer.EventType == WINDOW_BUFFER_SIZE_EVENT) {
				screen_resize();
				ch = TM_KEY_SCREEN_RESIZED;
				read = 1;
			}
		}

		else {
			read = 1;
		}
	} while(!read);
#else
	fflush(stdin);
	struct pollfd s_poll[2];
	s_poll[0].fd = fileno(stdin);
	s_poll[0].events = POLLIN;

	s_poll[1].fd = screen->signal_fd;
	s_poll[1].events = POLLIN;

	poll(s_poll, 2, win->input_timeout);

	if(s_poll[0].revents & POLLIN) {
		read(fileno(stdin), &ch, 1);
	}

	else if(s_poll[1].revents & POLLIN) {
		resize = 1;
	}
#endif
	if(win->flags & TM_FLAG_ECHO) {
		if((ret = tm_win_print(win, "%c", ch)) == TM_ERROR) {
			return ch;
		}

		tm_win_update(win);
	}

	*c = ch;

	if(resize) {
		return TM_SCREEN_RESIZE;
	}

	else {
		return 0;
	}
}

void tm_win_input_str(Tm_window* win, char* str, int max_size) { 
	int i = 0;
	char ch = 0;

	int og_flags = tm_win_get_flags(win);

	tm_win_flags(win, TM_FLAG_CURSOR_VISIBLE, 1);
	tm_win_flags(win, TM_FLAG_ECHO, 0);

	while(1) {
		tm_win_input_ch(win, &ch);

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
