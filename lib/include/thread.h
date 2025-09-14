#include <sys/types.h>
#define STACK_SIZE 4096 * 2

typedef void*(*thread_func_t)(void*);

typedef struct thread_t {
    int thread_id;
    void *args;
    thread_func_t func;
    
}thread_t;



void *create_stack(off_t size, int thread_id);

int thread_create(thread_t *tid, void *thread_func, void *args);

