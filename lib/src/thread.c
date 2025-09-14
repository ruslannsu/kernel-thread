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


int *thread_func_wrapper(void *args) {
	thread_t *thread_srtuct = (thread_t*)(args);
	thread_srtuct->func(thread_srtuct->args);
	while (thread_srtuct->join) {
		usleep(500);
	}

	return 0;
}


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


int thread_create(thread_t *tid, thread_func_t *thread_func, void *args) {
	static int thread_counter = 0;
	++thread_counter;

	char *stack = create_stack(10, thread_counter);

	thread_t *thread_struct = malloc(sizeof(thread_t));

	thread_struct->args = args;
	thread_struct->thread_id = thread_counter;
	thread_struct->func = thread_func;
	thread_struct->join = 0;
	thread_struct->return_value = NULL;

	int thread_id = clone(thread_func_wrapper, stack + STACK_SIZE, CLONE_VM |  CLONE_FILES | CLONE_THREAD | CLONE_SIGHAND | SIGCHLD, thread_struct);
	if (thread_id == -1) {
		printf("create error, %s \n", strerror(errno));
		return -1;
	}

	return thread_id;
}

int thread_join(thread_t *tid) {
	tid->join = 1;
}



	
	
