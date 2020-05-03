#ifndef H_THREADS
#define H_THREADS

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "helper.h"

extern pthread_mutex_t lock;

// Fonction principale que va lancer un thread :
// Va faire un nombre d'accès à la mémoire spécifié par la configuration
// et retournera le nombre de fois qu'il a eu un HIT
void* query_address(void* _context);

// Crée une liste de thread id pour pouvoir en lancer plusieurs
pthread_t* create_tid_array(int length);
void free_tid_array(pthread_t *tids);

// Lance les différents threads avec la fonction principale
void start_all_threads(pthread_t *tid_array, MemoryContext* context);

// Attends la fin de tous les threads et récupère la valeur de retour de query_address
// qui correspond en fait au nombre de hits
int* join_all_threads(pthread_t *tid_array, MemoryContext* context);

#endif
