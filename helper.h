#ifndef H_CONFIG
#define H_CONFIG

#include <stdio.h>


typedef struct Configuration {
    int frames; // Nombre de frame disponible dans la mémoire principale
    int page_size;
    int nb_page_secondary; // Nombre de pages dispo dans la mémoire secondaire
    int nb_threads;
    int nb_access; // Nombre d'accès demandés par thread
} Configuration;

void print_config(Configuration config);
void read_config(Configuration *config);

void random_address(int max);

#endif