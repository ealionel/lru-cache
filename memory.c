#include <pthread.h>
#include "memory.h"
#include "threads.h"

#define CACHE_HIT 1
#define CACHE_MISS 0

Page* create_page(int page_number) {
    Page* node = (Page*)malloc(sizeof(Page));

    node->page_number = page_number;
    node->left = NULL;
    node->right = NULL;

    return node;
}

Queue* create_queue(int max_frames) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));

    queue->front = NULL;
    queue->back = NULL;
    queue->max_frames = max_frames;
    queue->count = 0;

    // queue->frames = create_hash(max_frames);

    return queue;
}

// Le hash permet de vérifier en une seule opération si une page est présente
// dans la mémoire principale ou pas, sa valeur de hashage correspond au numéro
// de page dans la mémoire physique
Hash* create_hash(int capacity) {
    Hash* hash = (Hash*)malloc(sizeof(Hash));
    hash->capacity = capacity;

    hash->array = (Page**)malloc(sizeof(Page*) * capacity);

    for (int i = 0; i < capacity; i++) {
        hash->array[i] = NULL;
    }

    return hash;
}

void free_hash(Hash* hash) {
    free(hash->array);
    free(hash);
}

void free_queue(Queue* queue) {
    Page* it = queue->front;
    while (it != NULL) {
        Page* next;
        next = it->right;
        free(it);
        it = next;
    }

    // free(queue->frames);
}

int is_queue_full(Queue* queue) { return queue->count == queue->max_frames; }

int is_queue_empty(Queue* queue) { return queue->back == NULL; }

// Retire une frame de la queue
void dequeue(Queue* queue) {
    if (is_queue_empty(queue)) {
        // Si elle est vide on a rien à retirer
        return;
    }

    if (queue->front == queue->back) {
        // Pour le cas où il n'y aurait qu'un seul élément dans la queue
        queue->front = NULL;
    }

    Page* tmp = queue->back;

    queue->back = queue->back->left;

    if (queue->back) {
        queue->back->right = NULL;
    }

    free(tmp);
    queue->count -= 1;
}

Page* enqueue(Queue* queue, Hash* hash, unsigned int page_number) {
    Page* new_page = create_page(page_number);

    if (is_queue_full(queue)) {
        // La nouvelle page récupère l'adresse virtuelle de celle qui est
        // enlevée puisqu'elle est remplacée par celle-ci (LRU)
        new_page->virtual_page_number = queue->back->virtual_page_number;

        hash->array[queue->back->page_number] = NULL;
        dequeue(queue);
    } else {
        // Si jamais toutes les frames de la queue ne sont pas pleines, alors on
        // l'associe à l'adresse de page associée au nombre d'éléments dans la
        // queue Donc par exemple si notre queue a une capacité de 4 frames, et
        // qu'il contient 2 frames, alors la nouvelle page aura une adresse
        // virtuelle de 2 (3e element).
        new_page->virtual_page_number = queue->count;
    }

    if (is_queue_empty(queue)) {
        // Si la queue est vide avant, le premier élément est aussi le dernier
        // élément.
        queue->front = new_page;
        queue->back = new_page;
    } else {
        new_page->right = queue->front;
        queue->front->left = new_page;
        queue->front = new_page;
    }

    // On ajoute la page au tableau de hash pour pouvoir le détecter par la
    // suite
    hash->array[page_number] = new_page;

    queue->count++;

    return new_page;
}

int page_in_main_memory(Queue* q, Hash* h, unsigned int page_number) {
    return h->array[page_number] != NULL ? CACHE_HIT : CACHE_MISS;
}

int reference_page_lru(Queue* queue, Hash* hash, unsigned int page_number) {
    Page* page_requested = hash->array[page_number];

    pthread_mutex_lock(&lock);

    if (page_requested == NULL) {
        // Si la page n'a pas été trouvée dans la queue, on l'ajoute au début
        page_requested = enqueue(queue, hash, page_number);

    } else if (queue->front != page_requested) {
        // Si la page a été trouvée dans la queue, et qu'elle ne possède pas
        // qu'un unique élément on la remet au début tout en faisant attention à
        // bien modifier tous les liens de la liste chainée

        // if (queue->front == page_requested->left) {
        //     queue->front->left = page_requested;
        // }

        page_requested->left->right = page_requested->right;

        if (page_requested->right) {
            page_requested->right->left = page_requested->left;
        }

        if (queue->back == page_requested) {
            // C'est le cas où la page demandée se situe en fin de queue
            // elle est tout simplement remise au début de la queue.
            queue->back = page_requested->left;
            queue->back->right = NULL;
        }

        queue->front->left = page_requested;
        page_requested->right = queue->front;
        page_requested->left = NULL;

        queue->front = page_requested;
    }

    pthread_mutex_unlock(&lock);

    return page_requested->virtual_page_number;
}

int reference_address(Queue* queue, Hash* hash, unsigned int physical_address, unsigned int frame_size) {
    // printf("Requested : %d\n", physical_address);
    int virtual_page = reference_page_lru(queue, hash, get_page(physical_address, frame_size));


    // Translation vers l'adresse logique
    // en gros : page_i * framesize + @physique % framesize
    return get_page(virtual_page, frame_size) + get_offset(physical_address, frame_size);
}

void print_queue(Queue* queue) {
    if (is_queue_empty(queue)) {
        printf("Empty queue\n");
        return;
    }

    Page* it = queue->front;

    while (it != NULL) {
        printf("%d ", it->page_number);
        it = it->right;
    }
    printf("\n");
}

int get_page(int address, int frame_size) {
    return address / frame_size;
}

int get_offset(int address, int frame_size) { return address % frame_size; }