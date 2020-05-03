#include <stdio.h>
#include <pthread.h>

#include "helper.h"
#include "memory.h"

void *print_string(void *arg) {
    char *str = (char*) arg;

    printf("Thread : %s\n", str);
    return (void *) str;
}


int main() {
    int seed = time(NULL);

    Configuration config;

    read_config(&config);
    print_config(config);

    Queue* q = create_queue(config.frames);
    // Hash* virtual_mem = create_hash(config.frames);

    Hash* h = create_hash(config.nb_page_secondary);

    int test[20] = {1, 2, 3, 1, 1,7,6,5,8,7,10, 3, 3, 4, 5, 6};

    for (int i = 0; i < 15; i++) {
        reference_page_lru(q,h, test[i]);
        print_queue(q);
    }



    free_queue(q);
    free_hash(h);

    // pthread_t tid;
    // pthread_create(&tid, NULL, print_string, "Bonjour");
    // pthread_join(tid,);
}