#include "thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
void *thread_func(void *args) {
	for (size_t i = 0; i != 10; ++i) {
		printf("%s\n", "hello from thread");
		printf("%s\n", (char*)args);
	}
	
	int *ret = malloc(sizeof(int));
	if (ret == NULL) {
		return NULL;
	}
	*ret = 5;
	return (void*)ret;

	return NULL;
}


int main() {
	thread_desc t;

	int err = thread_create(&t, thread_func, "hello from args");

	if (err != 0) {
		printf("%s\n", strerror(err));
	}
	sleep(2);
	for (size_t i = 0; i != 2; ++i) {
		printf("%s\n", "hello from main");
	}


	printf("%d \n ", getpid());
	sleep(100);

	
	return 0;
}
