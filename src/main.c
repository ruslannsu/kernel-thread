#include "thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

 
void *thread_func(void *args, thread_t *tid) {
	for (size_t i = 0; i != 1000000; ++i) {
		printf("%d %s \n", i, "hello from thread1");
		if (i == 5000) {
			thread_exit(tid);
		}
		usleep(500);
	}
	return 0;
}

 
void *thread_func2(void *args, thread_t *tid) {
	for (size_t i = 0; i != 1000000; ++i) {
		printf("%d %s \n", i, "hello from thread2");
		usleep(500);
	}
	return 0;
}

int main() {
	
	thread_desc t;
	int err = thread_create(&t, thread_func, "hello from args");

	if (err != 0) {
		printf("%s\n", strerror(err));
	}
	
	
	sleep(5);

	return 0;
}
