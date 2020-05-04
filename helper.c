#include "helper.h"

#include <stdio.h>
#include <stdlib.h>

void print_config(Configuration config) {
    printf("---------- Config -----------\n");
    printf("frames:\t\t\t%d\n", config.frames);
    printf("page_size:\t\t%d\n", config.page_size);
    printf("nb_page_secondary:\t%d\n", config.nb_page_secondary);
    printf("nb_threads:\t\t%d\n", config.nb_threads);
    printf("nb_access:\t\t%d\n", config.nb_access);
    printf("-----------------------------\n");
}

void read_config(Configuration *config) {
    scanf("%d", &config->frames);
    scanf("%d", &config->page_size);
    scanf("%d", &config->nb_page_secondary);
    scanf("%d", &config->nb_threads);
    scanf("%d", &config->nb_access);
}

unsigned int random_address(unsigned int max) { return rand() % max; }

void print_stats(Configuration config, int *stats) {
    int total_hit = 0;
    int total_requests = config.nb_access * config.nb_threads;

    for (int i = 0; i < config.nb_threads; i++) {
        float thread_hit_rate = (float)stats[i] / (float)config.nb_access;
        printf("Thread[%d] :\t%d / %d hits\t%.2f%%\n", i + 1, stats[i], config.nb_access, thread_hit_rate * 100);
        total_hit += stats[i];
    }
    printf("-----------------------------\n");

    float hit_rate = (float)total_hit / (float)total_requests;

    printf("Total :\t\t%d / %d hits\n", total_hit, total_requests);
    printf("Hit Rate :\t%.2f%%\n", hit_rate * 100);
}