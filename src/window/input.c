#include "termmanip.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#else
#include <unistd.h>
#endif

int tm_win_input_ch(Tm_window* win) {
	int ret = 0;
	char ch[4096];
	*ch = 0;

	tm_win_update(win);

	if(win->flags & TM_FLAG_RAW) {	
		if((win->flags & TM_FLAG_INPUTBLOCK) == 0) {
#ifdef _WIN32
			INPUT_RECORD ip;
			
			DWORD events_read = 0;

			PeekConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &ip, 1, &events_read);
			
			if(events_read > 0) {
				ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &ip, 1, &events_read);

				if(ip.Event.KeyEvent.bKeyDown) {
					*ch = ip.Event.KeyEvent.uChar.AsciiChar;
				}
			}
#else
			read(fileno(stdin), ch, 1);
#endif
		}

		else {
			read(fileno(stdin), ch, 1);
		}

		if(win->flags & TM_FLAG_ECHO) {
			if((ret = tm_win_print(win, "%c", *ch)) == TM_ERROR) {
				return *ch;
			}

			tm_win_update(win);
		}
	}

	else {
		if((ret = tm_win_input_str(win, ch, 4096)) == TM_ERROR) {
			return ret;
		}
	}

	return *ch;
}

int tm_win_input_str(Tm_window* win, char* str, int max_size) { 
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

			if((ret = tm_win_cursor(win, tm_win_get_cursor_x(win) - 1, tm_win_get_cursor_y(win))) == TM_ERROR) {
				return ret;
			}

			if((ret = tm_win_putch(win, tm_win_get_background(win).disp, tm_win_get_background(win).attrib)) == TM_ERROR) {
				return ret;
			}

			if((ret = tm_win_cursor(win, tempX - 1, tempY)) == TM_ERROR) {
				return ret;
			}

			tm_win_update(win);

			continue;
		}

		if((ret = tm_win_print(win, "%c", ch)) == TM_ERROR) {
			continue;
		}

		if(i <= max_size) {
			str[i] = ch;
			i++;
		}

		tm_win_update(win);
	}

	str[i] = '\0';

	return 0;
}


