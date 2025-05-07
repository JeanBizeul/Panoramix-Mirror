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

#define POT_SIZE 3
#define REFILLS 3
#define VILLAGERS 1
#define NB_FIGHTS 5

extern int Refills_left;

extern pthread_mutex_t Pot_mutex;
extern pthread_mutex_t Refills_left_mutex;
extern sem_t Potions_sem;
extern sem_t Call_druid_sem;

typedef struct pot_s {
    unsigned int servings;
} pot_t;

typedef struct villager_s {
    unsigned int id;
    unsigned int nb_fights;
    pot_t *pot;
} villager_t;

typedef struct druid_s {
    unsigned int nb_refills;
    sem_t Druid_ready_sem;
    pot_t *pot;
} druid_t;

void *village_thread(void *village_struct);
void *druid_thread(void *druid_struct);

villager_t **create_villagers(unsigned int count, unsigned int nb_fights,
    pot_t *pot);
pot_t *create_pot(void);
druid_t *create_druid(unsigned int nb_refills, pot_t *pot);

bool init_semaphores(void);
bool init_mutexes(void);
bool init_shared(void);

void launch_panoramix(villager_t **villagers, druid_t *druid);
#endif /* !PANORAMIX_HPP_ */
