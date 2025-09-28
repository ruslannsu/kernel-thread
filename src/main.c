#include "thread.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ucontext.h>

 
void *thread_func(void *args, thread_t *tid) {
	for (size_t i = 0; i != 100000000; ++i) {
		printf("%d %s \n", i, "hello from thread1");
		test_cancel(tid);
	}
	return 0;
}

 
void *thread_func2(void *args, thread_t *tid) {
	for (size_t i = 0; i != 100000000; ++i) {
		printf("%d %s \n", i, "hello from thread2");
		test_cancel(tid);
	}
	return 0;
}

int main() {
	
	thread_desc t;
	int err = thread_create(&t, thread_func, "hello from args");

	if (err != 0) {
		printf("%s\n", strerror(err));
	}
	thread_desc t2;
	err = thread_create(&t2, thread_func2, "hello from args");
	sleep(3);
	thread_cancel(t);
	sleep(100);

	return 0;
}
