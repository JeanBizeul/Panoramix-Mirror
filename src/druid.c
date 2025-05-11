/*
** EPITECH PROJECT, 2025
** Panoramix-Mirror
** File description:
** druid
*/

#include <stdio.h>
#include "panoramix.h"

static void refill(druid_t *druid)
{
    pthread_mutex_lock(&Refills_left_mutex);
    pthread_mutex_lock(&Servings_left_mutex);
    Refills_left--;
    Servings_left = druid->pot_size;
    printf("Druid: Ah! Yes, yes, I'm awake! Working on it!"
        " Beware I can only make %u more refills after this one.\n",
        Refills_left);
    pthread_mutex_unlock(&Refills_left_mutex);
}

static bool can_refill(void)
{
    pthread_mutex_lock(&Refills_left_mutex);
    if (Refills_left == 0) {
        pthread_mutex_unlock(&Refills_left_mutex);
        return false;
    }
    pthread_mutex_unlock(&Refills_left_mutex);
    return true;
}

static bool all_villagers_sleeping(druid_t *druid)
{
    bool are_all_sleeping = false;

    pthread_mutex_lock(&Villagers_done_mutex);
    are_all_sleeping = (Villagers_done == druid->villager_count);
    pthread_mutex_unlock(&Villagers_done_mutex);
    return are_all_sleeping;
}

void *druid_thread(void *druid_struct)
{
    druid_t *druid = (druid_t *)druid_struct;

    printf("Druid: I'm ready... but sleepy...\n");
    Servings_left = druid->pot_size;
    sem_post(&druid->Druid_ready_sem);
    while (can_refill() && !all_villagers_sleeping(druid_struct)) {
        if (sem_trywait(&Call_druid_sem) == 0)
            refill(druid);
    }
    printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
    return NULL;
}
