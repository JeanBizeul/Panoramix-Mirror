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
    pthread_mutex_lock(&Pot_mutex);
    Refills_left--;
    druid->pot->servings = druid->pot->pot_size;
    printf("Druid: Ah! Yes, yes, I'm awake! Working on it!"
        " Beware I can only make %u more refills after this one.\n",
        Refills_left);
    for (unsigned int i = 0; i < druid->pot->servings; i++)
        sem_post(&Potions_sem);
    pthread_mutex_unlock(&Pot_mutex);
    pthread_mutex_unlock(&Refills_left_mutex);
}

void *druid_thread(void *druid_struct)
{
    druid_t *druid = (druid_t *)druid_struct;

    printf("Druid: I'm ready... but sleepy...\n");
    for (unsigned int i = 0; i < druid->pot->servings; i++)
        sem_post(&Potions_sem);
    sem_post(&druid->Druid_ready_sem);
    while (Refills_left > 0) {
        sem_wait(&Call_druid_sem);
        refill(druid);
    }
    printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
    return NULL;
}
