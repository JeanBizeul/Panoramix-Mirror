/*
** EPITECH PROJECT, 2025
** Panoramix-Mirror
** File description:
** panoramix
*/

#include <stdlib.h>
#include "panoramix.h"

villager_t **create_villagers(unsigned int count, unsigned int nb_fights,
    pot_t *pot)
{
    villager_t **villagers_list = malloc(sizeof(villager_t) * count + 1);

    if (villagers_list == NULL)
        return NULL;
    for (unsigned int i = 0; i < count; i++) {
        villagers_list[i] = malloc(sizeof(villager_t));
        if (villagers_list[i] == NULL) {
            free(villagers_list);
            return NULL;
        }
        villagers_list[i]->id = i;
        villagers_list[i]->nb_fights = nb_fights;
        villagers_list[i]->pot = pot;
    }
    villagers_list[count] = NULL;
    return villagers_list;
}

pot_t *create_pot(unsigned int size)
{
    pot_t *pot = malloc(sizeof(pot_t));

    if (pot == NULL)
        return NULL;
    pot->pot_size = size;
    pot->servings = pot->pot_size;
    return pot;
}

druid_t *create_druid(unsigned int nb_refills, unsigned int villagers_count,
    pot_t *pot)
{
    druid_t *druid = malloc(sizeof(druid_t));

    if (druid == NULL)
        return NULL;
    druid->nb_refills = nb_refills;
    druid->pot = pot;
    druid->villager_count = villagers_count;
    if (sem_init(&druid->Druid_ready_sem, 0, 0) == -1) {
        free(druid);
        return NULL;
    }
    return druid;
}

static unsigned int count_villagers(villager_t **villagers)
{
    unsigned int count = 0;

    while (villagers[count] != NULL)
        count++;
    return count;
}

void launch_panoramix(villager_t **villagers, druid_t *druid)
{
    unsigned int villager_count = count_villagers(villagers);
    pthread_t villager_threads[villager_count];
    pthread_t druid_thread_id;

    pthread_create(&druid_thread_id, NULL, druid_thread, druid);
    sem_wait(&druid->Druid_ready_sem);
    for (unsigned int i = 0; i < villager_count; i++)
        pthread_create(&villager_threads[i], NULL, village_thread,
            villagers[i]);
    for (unsigned int i = 0; i < villager_count; i++)
        pthread_join(villager_threads[i], NULL);
    pthread_join(druid_thread_id, NULL);
}
