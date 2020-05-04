#ifndef H_CONFIG
#define H_CONFIG

#include "memory.h"

typedef struct Configuration {
    int frames; // Nombre de frame disponible dans la mémoire principale
    int page_size; // Taille d'une page
    int nb_page_secondary; // Nombre de pages dispo dans la mémoire secondaire
    int nb_threads; // Nombre de threads enfants
    int nb_access; // Nombre d'accès demandés par thread
} Configuration;

// Structure contenant les références vers toutes les structures nécessaire pour faire tourner l'application.
// Ces références sont stockées dans une structure pour pouvoir tous les passer en argument de la routine des différents threads
typedef struct MemoryContext {
    Configuration config;
    Hash *memory_hash;
    Queue *queue;
} MemoryContext;

void print_config(Configuration config);
void read_config(Configuration *config);

// Affiche les statistiques après avoir lancé toutes les requêtes
void print_stats(Configuration config, int *stats);

// Génère un entier aléatoire compris entre 0 et max-1
unsigned int random_address(unsigned int max);

#endif