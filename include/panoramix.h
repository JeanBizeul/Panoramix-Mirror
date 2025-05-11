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

extern unsigned int Refills_left;
extern unsigned int Servings_left;
extern unsigned int Villagers_done;
extern bool Druid_called;

extern pthread_mutex_t Refills_left_mutex;
extern pthread_mutex_t Servings_left_mutex;
extern pthread_mutex_t Villagers_done_mutex;
extern pthread_mutex_t Druid_called_mutex;
extern pthread_cond_t Pot_refilled_cond;
extern sem_t Call_druid_sem;
extern sem_t Druid_ready_sem;

typedef struct villager_s {
    unsigned int id;
    unsigned int nb_fights;
} villager_t;

typedef struct druid_s {
    unsigned int nb_refills;
    unsigned int villager_count;
    unsigned int pot_size;
} druid_t;

void *village_thread(void *village_struct);
void *druid_thread(void *druid_struct);

villager_t **create_villagers(unsigned int count, unsigned int nb_fights);
druid_t *create_druid(unsigned int nb_refills, unsigned int villagers_count,
    unsigned int pot_size);
bool init_semaphores(void);
bool init_mutexes(void);
bool init_shared(unsigned int refill_count);

void launch_panoramix(villager_t **villagers, druid_t *druid);
#endif /* !PANORAMIX_HPP_ */
