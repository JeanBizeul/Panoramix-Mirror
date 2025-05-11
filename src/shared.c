/*
** EPITECH PROJECT, 2025
** Panoramix-Mirror
** File description:
** shared
*/

#include "panoramix.h"

unsigned int Refills_left;
unsigned int Servings_left;
unsigned int Villagers_done;
bool Druid_called;

pthread_mutex_t Refills_left_mutex;
pthread_mutex_t Servings_left_mutex;
pthread_mutex_t Villagers_done_mutex;
pthread_mutex_t Druid_called_mutex;
pthread_cond_t Pot_refilled_cond;
sem_t Call_druid_sem;
sem_t Druid_ready_sem;

bool init_semaphores(void)
{
    if (sem_init(&Call_druid_sem, 0, 0) == -1)
        return false;
    if (sem_init(&Druid_ready_sem, 0, 0) == -1)
        return false;
    return true;
}

bool init_mutexes(void)
{
    if (pthread_mutex_init(&Servings_left_mutex, NULL) != 0)
        return false;
    if (pthread_mutex_init(&Refills_left_mutex, NULL) != 0)
        return false;
    if (pthread_mutex_init(&Villagers_done_mutex, NULL) != 0)
        return false;
    if (pthread_mutex_init(&Druid_called_mutex, NULL) != 0)
        return false;
    return true;
}

bool init_conds(void)
{
    if (pthread_cond_init(&Pot_refilled_cond, NULL) != 0)
        return false;
    return true;
}

bool init_shared(unsigned int refill_count)
{
    Refills_left = refill_count;
    Villagers_done = 0;
    if (!init_semaphores())
        return false;
    if (!init_mutexes())
        return false;
    if (!init_conds())
        return false;
    return true;
}
