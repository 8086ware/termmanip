#include "termmanip.h"
#include "append_win.h"
#include <stdlib.h>
#include <string.h>
#include "exit_log.h"

int tm_win_background(Tm_window* win, int attrib) {
	char* temp = malloc(win->content_len * sizeof(char));

	if(temp == NULL) {
		exit_log("tm_win_background", "malloc", 1);
	}
	
	int temp_len = win->content_len;
	int cursor_x = win->cursor_x, cursor_y = win->cursor_y;	

	strncpy(temp, win->contents, temp_len);

	tm_win_attrib(win, attrib);

	tm_win_clear(win);	

	append_win(win, temp);

	win->cursor_x = cursor_x;
	win->cursor_y = cursor_y;

	return 0;
}
