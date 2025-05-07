/*
** EPITECH PROJECT, 2025
** Panoramix-Mirror
** File description:
** panoramix
*/

#ifndef PANORAMIX_HPP_
    #define PANORAMIX_HPP_
    #include <pthread.h>
    #include <semaphore.h>
    #include <stdbool.h>

#define POT_SIZE 5
#define REFILLS 3
#define VILLAGERS 10
#define NB_FIGHTS 3

int potions = POT_SIZE;
int refills_left = REFILLS;

pthread_mutex_t pot_mutex;
sem_t potions_sem;
sem_t call_druid_sem;

typedef struct villager_s {
    unsigned int id;
    unsigned int nb_fights;
} villager_t;

typedef struct druid_s {
    unsigned int id;
    unsigned int nb_refills;
} druid_t;

void *village_thread(void *village_struct);
void *druid_thread(void *druid_struct);

#endif /* !PANORAMIX_HPP_ */
