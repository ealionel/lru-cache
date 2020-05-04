#include "threads.h"

#include "memory.h"

void *query_address(void *_context) {
    MemoryContext *context = (MemoryContext *)_context;

    int *nb_hits = malloc(sizeof(int)); // Nombre de fois que la fonction
                                        // in_main_memory renvoie un CACHE_HIT
    *nb_hits = 0;

    for (int i = 0; i < context->config.nb_access; i++) {
        // Génère une adresse aléatoire comprise entre 0 et le nombre de page
        // dans la mémoire secondaire
        int rand_address = random_address((context->config.nb_page_secondary) * context->config.page_size);

        int in_memory =
            page_in_main_memory(context->queue, context->memory_hash, get_page(rand_address, context->config.page_size));

        if (in_memory) {
            // Si cette mémoire se trouve dans la mémoire principale on augmente
            // notre compteur
            (*nb_hits)++;
        }

        // On fait une demande d'adresse physique à notre Queue
        reference_address(context->queue, context->memory_hash, rand_address, context->config.page_size);

        // printf("\n[%d] %s %d:\t", i, in_memory ? "Y" : "N",
        // get_page(rand_address, context->config.page_size));
        // print_queue(context->queue);
        // print_queue("cocou");
    }

    return nb_hits;
}

pthread_t *create_tid_array(int length) {
    pthread_t *tid_array = (pthread_t *)malloc(sizeof(pthread_t) * length);
    return tid_array;
}

void start_all_threads(pthread_t *tid_array, MemoryContext *context) {
    for (int i = 0; i < context->config.nb_threads; i++) {
        pthread_create(&tid_array[i], NULL, query_address, context);
    }
}

int *join_all_threads(pthread_t *tid_array, MemoryContext *context) {
    void *return_val;
    int *stats = (int *)malloc(sizeof(int) * context->config.nb_threads);

    for (int i = 0; i < context->config.nb_threads; i++) {
        pthread_join(tid_array[i], &return_val);

        // Déréférence la valeur de retour pour la sauvegarder dans notre
        // tableau
        stats[i] = *((int *)return_val);

        // Puis libère le pointeur qui était alloué dynamiquement dans
        // request_address
        free(return_val);
    }

    return stats;
}

void free_tid_array(pthread_t *tids) { free(tids); }
