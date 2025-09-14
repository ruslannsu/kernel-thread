#include "thread.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	thread_create(NULL, main, NULL);
	return 0;
}
