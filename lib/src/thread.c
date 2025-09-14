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



void *create_stack(off_t size, int thread_id) {
	void *stack_ptr;
	int stack_fd;
	char *stack_f = malloc(30);
	snprintf(stack_f, sizeof(stack_f), "stack-%d", thread_id);   
	stack_fd = open(stack_f, O_RDWR | O_CREAT, 0660);
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
	if (stack_ptr == MAP_FAILED) {
		printf("stack maping failed %s\n", strerror(errno));
	}

	return stack_ptr;
}


int thread_create(thread_t *tid, void *thread_func, void *args) {

	char *stack = create_stack(10, 3);

	int thread_id = clone(thread_func, stack + STACK_SIZE, CLONE_VM |  CLONE_FILES | CLONE_THREAD | CLONE_SIGHAND | SIGCHLD, NULL);
	if (thread_id == -1) {
		printf("create error, %s \n", strerror(errno));
		return -1;
	}

	return thread_id;
}



	
	
