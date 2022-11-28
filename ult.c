#include <pth.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *print_message_function(void *ptr);

#define THREAD_COUNT 24

void main() {
    pth_init();

    pth_t threads[THREAD_COUNT];
    char messages[THREAD_COUNT][12];
    int irets[THREAD_COUNT];

    /* Create independent threads each of which will execute function */

    for (int i = 0; i < THREAD_COUNT; i++) {
        sprintf(messages[i], "Message %d", i);
        threads[i] = pth_spawn(PTH_ATTR_DEFAULT, print_message_function,
                               (void *)messages[i]);
    }

    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */

    for (int i = 0; i < THREAD_COUNT; i++) {
        void *ret = &irets[i];
        pth_join(threads[i], &ret);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        printf("Thread %d returns: %d\n", i, irets[i]);
    }

    pth_exit(0);
}

void *print_message_function(void *ptr) {
    // busy wait
    for (u_int32_t i = __UINT32_MAX__; i > 0; i--)
        ;
    char *message;
    message = (char *)ptr;
    printf("%s \n", message);
}
