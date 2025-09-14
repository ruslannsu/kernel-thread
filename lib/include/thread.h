#define STACK_SIZE 4096 * 2


typedef struct thread_t {
    int a;
}thread_t;



void *create_stack(off_t size);

int thread_create(thread_t *tid, void *thread_func, void *args);

