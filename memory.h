#ifndef H_MEMORY
#define H_MEMORY

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Page {
    unsigned int page_number;
    unsigned int virtual_page_number;
    struct Page* left;   // Page précédente
    struct Page* right;  // Page suivante
} Page;

typedef struct Queue {
    Page* front;  // Première page du FIFO (celle qu'on vient d'ajouter ou
                  // mettre à jour)
    Page*
        back;  // Dernière page du FIFO (celle qui va être supprimée si jamais)
    // Hash* frames;
    unsigned int count;
    unsigned int max_frames;
} Queue;

typedef struct Hash {
    int capacity;
    Page** array;
} Hash;

Page* create_page(int page_number);

Queue* create_queue(int max_frames);

Hash* create_hash(int capacity);

void free_hash(Hash* hash);

void free_queue(Queue* queue);

int is_queue_full(Queue* queue);

int is_queue_empty(Queue* queue);

// Retire une page de la queue
void dequeue(Queue* queue);

// Ajoute une page au début de la queue et retourne un pointeur vers cette page
Page* enqueue(Queue* queue, Hash* hash, unsigned int page_number);

// Retourne CACHE_HIT si la page page_number est dans la mémoire principale
// Sinon retourne CACHE_MISS
int page_in_main_memory(Queue* q, Hash* h, unsigned int page_number);

// Permet de faire une demande de mémoire par rapport à une page physique
int reference_page_lru(Queue* queue, Hash* hash, unsigned int page_number);

// Permet de faire une demande de mémoire par rapport à une adresse physique
int reference_address(Queue* queue, Hash* hash, unsigned int physical_address, unsigned int frame_size);

void print_queue(Queue* queue);

int get_page(int address, int frame_size);
int get_offset(int address, int frame_size);

#endif