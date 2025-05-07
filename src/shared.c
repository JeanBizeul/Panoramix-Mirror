/*
** EPITECH PROJECT, 2025
** Panoramix-Mirror
** File description:
** shared
*/

#include "panoramix.h"

int Refills_left;

pthread_mutex_t Pot_mutex;
pthread_mutex_t Refills_left_mutex;
sem_t Potions_sem;
sem_t Call_druid_sem;

bool init_semaphores(void)
{
    if (sem_init(&Potions_sem, 0, 0) == -1)
        return false;
    if (sem_init(&Call_druid_sem, 0, 0) == -1)
        return false;
    return true;
}

bool init_mutexes(void)
{
    if (pthread_mutex_init(&Pot_mutex, NULL) != 0)
        return false;
    if (pthread_mutex_init(&Refills_left_mutex, NULL) != 0)
        return false;
    return true;
}

bool init_shared(unsigned int refill_count)
{
    Refills_left = refill_count;
    if (!init_semaphores())
        return false;
    if (!init_mutexes())
        return false;
    return true;
}
