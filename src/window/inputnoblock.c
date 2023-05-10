#include "termmanip.h"
#include <unistd.h>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

int tm_win_input_ch_noblock(Tm_window* win) {
	int ret = 0;
	char ch = 0;

	tm_win_update(win);

#ifdef _WIN32
	INPUT_RECORD ip = {0};
	DWORD events_read = 0;
	DWORD bytes_read = 0;

	if(PeekConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &ip, 1, &events_read) == 0) {
		exit_log("tm_win_input_ch_noblock", "PeekConsoleInput", 1);
	}

	if(events_read > 0) {
		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &ip, 1, &events_read);
		ch = ip.Event.KeyEvent.uChar.AsciiChar;
	}

	if(ip.EventType != KEY_EVENT) {
		return 0;
	}
#else
	terminal_inputblock(0);
	read(fileno(stdin), ch, 1);
	terminal_inputblock(1);
#endif
	if(win->flags & TM_FLAG_ECHO) {
		if((ret = tm_win_print(win, "%c", ch)) == TM_ERROR) {
			return ch;
		}

		tm_win_update(win);
	}

	return ch;
}


int tm_win_input_str_noblock(Tm_window* win, char* str, int max_size, int* length) { 
	int ch = 0;
	int ret = 0;

#ifdef _WIN32
	INPUT_RECORD ip = {0};
	DWORD events_read = 0;
	DWORD bytes_read = 0;

	if(PeekConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &ip, 1, &events_read) == 0) {
		exit_log("tm_win_input_ch_noblock", "PeekConsoleInput", 1);
	}

	if(events_read > 0) {
		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &ip, 1, &events_read);
		ch = ip.Event.KeyEvent.uChar.AsciiChar;
	}
#else
	terminal_inputblock(0);
	read(fileno(stdin), ch, 1);
	terminal_inputblock(1);
#endif

	if(ch == '\n' || ch == '\r') {
		str[*length] = '\0';
		return TM_INPUT_FINISHED;
	}

	if(ch == '\177' || ch == '\b') {
		if(*length > 0) {
			str[*length] = '\0';
			(*length)--;
			int tempX = win->cursor_x;
			int tempY = win->cursor_y;

			if((ret = tm_win_cursor(win, win->cursor_x - 1, win->cursor_y)) == TM_ERROR) {
				return ret;
			}

			if((ret = tm_win_print(win, " ")) == TM_ERROR) {
				return ret;
			}

			if((ret = tm_win_cursor(win, tempX - 1, tempY)) == TM_ERROR) {
				return ret;
			}

			tm_win_update(win);
		}
	}

	else if(ch != 0) {
		if(*length <= max_size) {
			str[*length] = ch;
			(*length)++;

			if((ret = tm_win_print(win, "%c", ch)) == TM_ERROR) {
				return ret;
			}

			tm_win_update(win);
		}
	}

	return 1;
}
