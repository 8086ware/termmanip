#include "exit_log.h"
#include <stdio.h>
#include <stdlib.h>

void exit_log(char* func, char* msg, int id) {
	fprintf(stderr, "%s() Error %d: %s", func, id, msg);
	getchar();
	exit(-1);
}
