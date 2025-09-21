#include <sys/types.h>
#define STACK_SIZE 4096 * 16
#define FILE_NAME_SIZE 128
#define SLEEP_TIME 500
#define PAGE_SIZE 4096



typedef long long thread_desc;

typedef void*(*thread_func_t)(void*);

typedef struct thread_t {
    int thread_id;
    thread_func_t func;
    void *args;
    void *return_value;
    volatile int joined;   
    volatile int detached; 
    volatile int exited;
}thread_t;



int stack_create(off_t size, int thread_id, void **stack);

int thread_create(thread_desc *tid, thread_func_t thread_func, void *args);

int thread_join(thread_t *tid, void **return_value);



