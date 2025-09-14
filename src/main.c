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
	*ret = 5;
	return (void*)ret;
}


int main() {
	thread_desc t;

	int err = thread_create(&t, thread_func, "hello from args");
	if (err != 0) {
		printf("%s\n", strerror(err));
	}

	void *ret_val;
	err = thread_join((thread_t*)t, &ret_val);
	if (err != 0) {
		printf("%s\n", strerror(err));
	}
	
	printf("%d \n",  *(int*)ret_val);
	return 0;
}
