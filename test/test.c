#include "termmanip.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(void) {
	tm_init();

	tm_win_border(default_win);

	int i = 0;
	int disp = 0;
	char k[32];

	while(1) {
		i++;
		if(clock() % CLOCKS_PER_SEC == 0) {
			disp = i;
			i = 0;
			sprintf(k, "%d, seconds: %f",  disp, (float)clock() / CLOCKS_PER_SEC);	
			tm_cursor(1, 1);
			tm_print_str(k);
			tm_update();
		}
	}

}
