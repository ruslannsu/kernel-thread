#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
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







int thread_func_wrapper(void *args) {
	thread_t *thread_srtuct = (thread_t*)(args);
	thread_srtuct->return_value = thread_srtuct->func(thread_srtuct->args);
	thread_srtuct->exited = 1;

	if (!thread_srtuct->detached) {
		while (!thread_srtuct->joined) {
			usleep(SLEEP_TIME);
		}
	}

	return 0;
}

int stack_create(off_t size, int thread_id, void **stack_ptr) {
	int stack_fd;
	char *stack_f = malloc(FILE_NAME_SIZE);
	if (stack_f == NULL) {
		return -1;
	}

	snprintf(stack_f, FILE_NAME_SIZE, "stack-%d", thread_id);   
	stack_fd = open(stack_f, O_RDWR | O_CREAT, 0660);
	if (stack_fd == -1) {
		return -1;
	}

	int frt_err = ftruncate(stack_fd, 0);
	if (frt_err == -1) {
		return -1;
	}

	frt_err = ftruncate(stack_fd, size);
	if (frt_err == -1) {
		return -1;
	}

	*stack_ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, stack_fd, 0);
	if (*stack_ptr == MAP_FAILED) {
		return -1;
	}

	
	return 0;
}


int thread_create(thread_desc *thread_ptr, thread_func_t thread_func, void *args) {

	static int thread_counter = 0;
	++thread_counter;


	if (thread_func == NULL) {
		return EINVAL;
	}

	void *stack_buffer;
	int err = stack_create(STACK_SIZE, thread_counter, &stack_buffer);
	if (err == -1) {
		return EAGAIN;
	}
	void *stack_top = (char*)stack_buffer + STACK_SIZE;


	thread_t *thread_struct = (thread_t*)(stack_top);
	thread_struct->args = args;
	thread_struct->thread_id = thread_counter;
	thread_struct->func = thread_func;
	thread_struct->joined = 0;
	thread_struct->detached = 0;
	thread_struct->return_value = NULL;



	int thread_id = clone(thread_func_wrapper, (char*)stack_top - sizeof(thread_t), CLONE_VM |  CLONE_FILES | CLONE_THREAD | CLONE_SIGHAND | SIGCHLD, thread_struct);
	if (thread_id == -1) {
		return EINVAL;
	}

	void *stack_bottom = (char*)stack_top - STACK_SIZE;
	mprotect(stack_bottom, PAGE_SIZE, PROT_NONE);

	
	*thread_ptr =  (thread_desc)thread_struct;

	return 0;
	
}


int thread_join(thread_t *tid, void **return_value) {
	if (tid->detached == 1) {
		return EINVAL;
	}

	if (tid == NULL) {
		return ESRCH;
	}

	if (return_value == NULL) {
		return EINVAL;
	}

	while (!tid->exited) {
		usleep(SLEEP_TIME);
	}

	*return_value = tid->return_value;
	tid->joined = 1;
	return 0;	
}



	
	
