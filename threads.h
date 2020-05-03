#ifndef H_THREADS
#define H_THREADS

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

void* query_address(void* void_nb_requests) {
    int* nb_requests = (int*) void_nb_requests;

    for (int i = 0; i < *nb_requests; i++) {
        reference_address()
    }
}


#endif
