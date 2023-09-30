#include "termmanip.h"
#include <stdio.h>
#include <stdarg.h>
#include "terminal.h"
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#else
#include <poll.h>
#include <unistd.h>
#endif

Tm_input tm_win_input(Tm_window* win) {
	Tm_input input = {0};

	tm_win_update(win);
#ifdef _WIN32
	_Bool read_input = 0;
	do {
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		INPUT_RECORD buffer;
		if(WaitForSingleObject(GetStdHandle(STD_INPUT_HANDLE), win->input_timeout) == WAIT_OBJECT_0) {
			DWORD bytes_read;
			ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &buffer, 1, &bytes_read);

			if(buffer.EventType == KEY_EVENT) {
				if(buffer.Event.KeyEvent.dwControlKeyState & RIGHT_ALT_PRESSED || buffer.Event.KeyEvent.dwControlKeyState & LEFT_ALT_PRESSED) {
					input.alt_down = 1;
					continue;
				}

				if(buffer.Event.KeyEvent.dwControlKeyState & RIGHT_CTRL_PRESSED || buffer.Event.KeyEvent.dwControlKeyState & LEFT_CTRL_PRESSED) {
					input.ctrl_down = 1;
					continue;
				}

				if(buffer.Event.KeyEvent.bKeyDown == TRUE) {
					input.key = buffer.Event.KeyEvent.uChar.AsciiChar;
					read_input = 1;
				}

			}

			else if(buffer.EventType == WINDOW_BUFFER_SIZE_EVENT) {
				terminal_resize();
				input.terminal_resized = 1;
				read_input = 1;
			}
		}

		else {
			read_input = 1;
		}
#else
		fflush(stdin);
		struct pollfd s_poll[2];
		s_poll[0].fd = fileno(stdin);
		s_poll[0].events = POLLIN;
		s_poll[0].revents = 0;

		s_poll[1].fd = terminal->signal_fd;
		s_poll[1].events = POLLIN;
		s_poll[1].revents = 0;

		poll(s_poll, 2, win->input_timeout);

		if(s_poll[0].revents & POLLIN) {
			read(fileno(stdin), &input.key, 1);

			if(input.key == TM_KEY_ESC) {
				poll(s_poll, 1, 0);
				if(s_poll[0].revents & POLLIN) {
					char escape_input[10];		
					read(fileno(stdin), &escape_input[0], 1);

					poll(s_poll, 1, 0);
					
					if(s_poll[0].revents & POLLIN) {
						read(fileno(stdin), &escape_input[1], 1);
					}
					
					else {
						input.key = escape_input[0];
						input.alt_down = 1;
					}
				}
			}

			if(input.key <= 32) {
				input.key += 64;
				input.ctrl_down = 1;
			}

			read_input = 1;
		}

		else if(s_poll[1].revents & POLLIN) {
			char buf[1024];
			read(terminal->signal_fd, &buf, 1024);
			terminal_resize();
			input.terminal_resized = 1;
			read_input = 1;
		}
#endif
	} while(!read);

	if(input.key >= 32 && input.key <= 127) {
		if(win->flags & TM_FLAG_ECHO) {
			if(tm_win_print(win, "%c", input.key) == TM_ERROR) {
				return input;
			}

			tm_win_update(win);
		}
	}

	return input;
}

void tm_win_input_str(Tm_window* win, char* str, int max_size) { 
	int i = 0;
	Tmkey_T ch = 0;

	int og_flags = tm_win_get_flags(win);

	tm_win_flags(win, TM_FLAG_CURSOR_VISIBLE, 1);
	tm_win_flags(win, TM_FLAG_ECHO, 0);

	while(1) {
		ch = tm_win_input(win).key;

		if(ch <= 127) {
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
	}

	str[i] = '\0';

	tm_win_flags(win, TM_FLAG_ALL, 0);
	tm_win_flags(win, og_flags, 1);

	tm_win_print(win, "\n");
}

void tm_win_input_strf(Tm_window* win, char* str, ...) {
	char new_str[4096];
	tm_win_input_str(win, new_str, 4096);

	va_list list;

	va_start(list, str);

	vsscanf(new_str, str, list);

	va_end(list);
}
