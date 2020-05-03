#include <stdio.h>
#include <time.h>
#include <pthread.h>

#include "helper.h"
#include "memory.h"
#include "threads.h"

pthread_mutex_t lock;

int main() {
    srand(time(NULL));

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex failed to initialize");
        return EXIT_FAILURE;
    }

    Configuration config;

    read_config(&config);
    print_config(config);

    Queue* q = create_queue(config.frames);
    Hash* h = create_hash(config.nb_page_secondary);

    MemoryContext* context = (MemoryContext*) malloc(sizeof(MemoryContext));

    context->config = config;
    context->queue = q;
    context->memory_hash = h;

    pthread_t* tids = create_tid_array(config.nb_threads);

    start_all_threads(tids, context);
    int *stats = join_all_threads(tids, context);

    print_stats(config, stats);

    free(context);
    free_queue(q);
    free_hash(h);
    free(stats);
    free_tid_array(tids);

    pthread_mutex_destroy(&lock);

    return EXIT_SUCCESS;
}