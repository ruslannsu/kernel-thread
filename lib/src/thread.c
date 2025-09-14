#define _GNU_SOURCE 
#include <stdio.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "../include/thread.h"
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>



void *create_stack(off_t size) {
	void *stack_ptr;
	int stack_fd;

	stack_fd = open("./stack", O_RDWR | O_CREAT, 0660);
	if (stack_fd == -1) {
		printf("stack creation failed %s\n", strerror(errno));
	}

	int frt_err = ftruncate(stack_fd, 0);
	if (frt_err == -1) {
		printf("frt failer %s\n", strerror(errno));
	}

	frt_err = ftruncate(stack_fd, size);
	if (frt_err == -1) {
		printf("frt failer %s\n", strerror(errno));
	}

	stack_ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, stack_fd, 0);
	return stack_ptr;
}


int thread_create(thread_t *tid, void *thread_func, void *args) {

	char *stack = create_stack(10);

	int thread_id = clone(thread_func, stack + STACK_SIZE, CLONE_VM |  CLONE_FILES | CLONE_THREAD | CLONE_SIGHAND | SIGCHLD, NULL);
	if (thread_id == -1) {
		printf("create error, %s \n", strerror(errno));
		return -1;
	}

	return thread_id;
}


int main() {
	int t = thread_create(NULL, main, NULL);
	return 0;
}

	
	
