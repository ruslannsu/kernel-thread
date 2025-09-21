#include "thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
void *thread_func(void *args) {
	int *ret = malloc(sizeof(int));
	if (ret == NULL) {
		return NULL;
	}
	*ret = 5;
	return (void*)ret;
}

int main() {
	printf("%d \n ", getpid());
	thread_desc t;
	int err = thread_create(&t, thread_func, "hello from args");

	if (err != 0) {
		printf("%s\n", strerror(err));
	}
	void *ret;
	err = thread_join(t, &ret);
	if (err != 0) {
		printf("%s\n", strerror(err));
	}

	printf("%d\n", *((int*)ret));
	return 0;
}
