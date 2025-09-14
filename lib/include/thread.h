#include <sys/types.h>
#define STACK_SIZE 4096 * 2

typedef void*(*thread_func_t)(void*);

typedef struct thread_t {
    int thread_id;
    thread_func_t func;
    void *args;
    void *return_value;
    int join;    
}thread_t;



void *create_stack(off_t size, int thread_id);

int thread_create(thread_t *tid, thread_func_t *thread_func, void *args);

