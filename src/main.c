#include "thread.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	thread_create(NULL, main, NULL);
	thread_create(NULL, main, NULL);
	printf("okay!");
	return 0;
}
