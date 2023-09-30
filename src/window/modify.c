#include "termmanip.h"
#include <stdlib.h>
#include "error.h"
#include <memory.h>

int tm_win_modify(Tm_window* win, int x, int y, int columns, int rows) {
	int scr_x, scr_y;

	tm_get_scrsize(&scr_x, &scr_y);

	if(rows <= 0) {
		rows = 1;
	}

	if(columns <= 0) {
		columns = 1;
	}

	if(x < 0) {
		x = 0;
	}

	if(y < 0) {
		y = 0;
	}

	if(x + columns > scr_x) {
		columns -= scr_x - x;
	}

	if(y + rows > scr_y) {
		rows -= scr_y - y;
	}

	win->position_x = x;
	win->position_y = y;

	win->columns = columns;
	win->rows = rows;
	
	if(win->columns > win->buffer_columns) {
		int og_buffer_cols = win->buffer_columns, og_buffer_rows = win->buffer_rows;

		Tm_char* temp = malloc(sizeof(Tm_char) * og_buffer_cols * og_buffer_rows);

		memcpy(temp, win->buffer, sizeof(Tm_char) * og_buffer_cols * og_buffer_rows);

		win->buffer_columns = win->columns;

		win->buffer = realloc(win->buffer, sizeof(Tm_char) * win->columns * win->buffer_rows);

		if(win->buffer == NULL) {
			tm_set_error(TM_OUT_OF_MEM);
			return TM_ERROR;
		}

		int temp_x = tm_win_get_cursor_x(win);
		int temp_y = tm_win_get_cursor_y(win);

		int temp_buffer_x = tm_win_get_buffer_pos_x(win);
		int temp_buffer_y = tm_win_get_buffer_pos_y(win);
		
		for(int y = 0; y < win->buffer_rows; y++){ 
			for(int x = 0; x < win->buffer_columns; x++){ 
				tm_win_cursor(win, x, y);
				tm_win_putch(win, ' ', 0);
			}
		}

		for(int y = 0; y < og_buffer_rows; y++){ 
			for(int x = 0; x < og_buffer_cols; x++){ 
				tm_win_cursor(win, x, y);
				tm_win_putch(win, temp[y * og_buffer_cols + x].disp, temp[y * og_buffer_cols + x].attrib);
			}
		}

		win->buffer_position_x = temp_buffer_x;
		win->buffer_position_y = temp_buffer_y;
		tm_win_cursor(win, temp_x, temp_y);

		free(temp);
	}

	if(win->rows > win->buffer_rows) {
		int og_buffer_cols = win->buffer_columns, og_buffer_rows = win->buffer_rows;

		Tm_char* temp = malloc(sizeof(Tm_char) * og_buffer_cols * og_buffer_rows);

		memcpy(temp, win->buffer, sizeof(Tm_char) * og_buffer_cols * og_buffer_rows);

		win->buffer_rows = win->rows;

		win->buffer = realloc(win->buffer, sizeof(Tm_char) * win->buffer_columns * win->rows);

		if(win->buffer == NULL) {
			tm_set_error(TM_OUT_OF_MEM);
			return TM_ERROR;
		}

		int temp_x = tm_win_get_cursor_x(win);
		int temp_y = tm_win_get_cursor_y(win);

		int temp_buffer_x = tm_win_get_buffer_pos_x(win);
		int temp_buffer_y = tm_win_get_buffer_pos_y(win);
		
		for(int y = 0; y < win->buffer_rows; y++){ 
			for(int x = 0; x < win->buffer_columns; x++){ 
				tm_win_cursor(win, x, y);
				tm_win_putch(win, tm_win_get_background(win).disp, tm_win_get_background(win).attrib);
			}
		}

		for(int y = 0; y < og_buffer_rows; y++){ 
			for(int x = 0; x < og_buffer_cols; x++){ 
				tm_win_cursor(win, x, y);
				tm_win_putch(win, temp[y * og_buffer_cols + x].disp, temp[y * og_buffer_cols + x].attrib);
			}
		}

		win->buffer_position_x = temp_buffer_x;
		win->buffer_position_y = temp_buffer_y;

		tm_win_cursor(win, temp_x, temp_y);

		free(temp);
	}

	return 0;
}

