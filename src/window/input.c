#include "termmanip.h"
#include <stdio.h>
#include <stdarg.h>
#include "terminal.h"
#include <ctype.h>
#include "process_esc_input.h"
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#else
#include <poll.h>
#include <unistd.h>
#endif

Tm_input tm_win_input(Tm_window* win) {
	Tm_input input = {0};

	input.key = TM_KEY_NONE;
	_Bool read_input = 0;

	tm_win_update(win);

	if(terminal->resized) {
		if(win->flags & TM_FLAG_TERMINAL_INPUT) {
			input.terminal_resized = 1;
			read_input = 1;
		}

		terminal->resized = 0;
	}

	char escape_input[120];
	int escape_s_amount = 0;

	int remaining_time = win->input_timeout;

	if(!read_input) {
		do {
			if(remaining_time < 0 && win->input_timeout >= 0) {
				remaining_time = 0;
			}
#ifdef _WIN32
			INPUT_RECORD buffer;
			FILETIME start_time;
			GetSystemTimeAsFileTime(&start_time);

			if(WaitForSingleObject(GetStdHandle(STD_INPUT_HANDLE), remaining_time) == WAIT_OBJECT_0) {
				FILETIME elapsed_time;
				GetSystemTimeAsFileTime(&elapsed_time);

				ULARGE_INTEGER start;

				start.LowPart = start_time.dwLowDateTime;
				start.HighPart = start_time.dwHighDateTime;

				ULARGE_INTEGER elapsed;

				elapsed.LowPart = elapsed_time.dwLowDateTime;
				elapsed.HighPart = elapsed_time.dwHighDateTime;

				remaining_time -= (elapsed.QuadPart - start.QuadPart) / 10000;

				DWORD bytes_read;

				ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &buffer, 1, &bytes_read);

				if(buffer.EventType == KEY_EVENT) {
					if(buffer.Event.KeyEvent.uChar.AsciiChar == TM_KEY_ESC) {
						while(bytes_read != 0) {
							GetNumberOfConsoleInputEvents(GetStdHandle(STD_INPUT_HANDLE), &bytes_read);

							if(bytes_read > 0) {
								ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &buffer, 1, &bytes_read);
								if(buffer.Event.KeyEvent.bKeyDown) {
									escape_input[escape_s_amount] = buffer.Event.KeyEvent.uChar.AsciiChar;
									escape_s_amount++;
								}
							}
						}

						escape_input[escape_s_amount] = '\0';
						process_esc_input(&input, escape_input);
						read_input = 1;
					}

					else {
						if(buffer.Event.KeyEvent.bKeyDown) {
							input.key = buffer.Event.KeyEvent.uChar.AsciiChar;
							if(input.key != 0) {
								read_input = 1;
							}
						}
					}
				}

				else if(buffer.EventType == WINDOW_BUFFER_SIZE_EVENT) {
					terminal_resize();
					if(win->flags & TM_FLAG_TERMINAL_INPUT) {
						input.terminal_resized = 1;
						read_input = 1;
					}
				}
			}

			else {
				read_input = 1;
			}

#else
			struct pollfd s_poll[2];
			s_poll[0].fd = fileno(stdin);
			s_poll[0].events = POLLIN;
			s_poll[0].revents = 0;

			s_poll[1].fd = terminal->signal_fd;
			s_poll[1].events = POLLIN;
			s_poll[1].revents = 0;

			struct timespec ts_start;

			clock_gettime(CLOCK_REALTIME, &ts_start);

			poll(s_poll, 2, remaining_time);

			if(s_poll[0].revents & POLLIN || s_poll[1].revents & POLLIN) {
				struct timespec ts_elapsed;
				clock_gettime(CLOCK_REALTIME, &ts_elapsed);

				int elapsed = (ts_elapsed.tv_sec * 1000 + ts_elapsed.tv_nsec / 1000000) - (ts_start.tv_sec * 1000 + ts_start.tv_nsec / 1000000);

				remaining_time -= elapsed;

			}

			if(s_poll[0].revents & POLLIN) {
				read(fileno(stdin), &input.key, 1);

				if(input.key == TM_KEY_ESC) {
					do {
						poll(s_poll, 1, 0);

						if(s_poll[0].revents & POLLIN) {
							read(fileno(stdin), &escape_input[escape_s_amount], 1);
							escape_s_amount++;
						}
					} while(s_poll[0].revents & POLLIN);

					escape_input[escape_s_amount] = '\0';
					input.key = TM_KEY_NONE;
					process_esc_input(&input, escape_input);
				}

				read_input = 1;
			}

			else if(s_poll[1].revents & POLLIN) {
				char buf[1024];
				read(terminal->signal_fd, &buf, 1024);
				terminal_resize();
				if(win->flags & TM_FLAG_TERMINAL_INPUT) {
					input.terminal_resized = 1;
					read_input = 1;
				}
			}

			else {
				read_input = 1;
			}
#endif
		} while(!read_input);
	}
	if((input.key < 32 && input.key > 0) || input.key == 127) {
		input.ctrl_character = input.key;

		if(input.key == 127) {
			input.key = TM_KEY_QUESTION;
		}

		input.key += 64;

		input.ctrl_down = 1;
	}

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
	Tm_input t = {0};

	int og_flags = tm_win_get_flags(win);

	tm_win_flags(win, TM_FLAG_CURSOR_VISIBLE, 1);
	tm_win_flags(win, TM_FLAG_ECHO, 0);

	while(1) {
		t = tm_win_input(win);

		if(t.key <= 127) {
			if(t.ctrl_character == '\n' || t.ctrl_character == '\r') {
				break;
			}

			if(t.ctrl_character == '\177' || t.ctrl_character == '\b') {
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



			if(tm_win_print(win, "%c", t.key) != TM_ERROR) {
				if(i <= max_size) {
					str[i] = t.key;
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
