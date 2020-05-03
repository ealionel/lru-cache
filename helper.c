#include <stdio.h>

#include "helper.h"

void print_config(Configuration config) {
    printf("------- Config --------\n");
    printf("frames:\t\t\t%d\n", config.frames);
    printf("page_size:\t\t%d\n", config.page_size);
    printf("nb_page_secondary:\t%d\n", config.nb_page_secondary);
    printf("nb_threads:\t\t%d\n", config.nb_threads);
    printf("nb_access:\t\t%d\n", config.nb_access);
}

void read_config(Configuration *config) {
    scanf("%d", &config->frames);
    scanf("%d", &config->page_size);
    scanf("%d", &config->nb_page_secondary);
    scanf("%d", &config->nb_threads);
    scanf("%d", &config->nb_access);
}