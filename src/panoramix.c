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
    };
    villagers_list[count] = NULL;
    return villagers_list;
}

pot_t *create_pot(void)
{
    pot_t *pot = malloc(sizeof(pot_t));

    if (pot == NULL)
        return NULL;
    pot->servings = POT_SIZE;
    return pot;
}

druid_t *create_druid(unsigned int nb_refills, pot_t *pot)
{
    druid_t *druid = malloc(sizeof(druid_t));

    if (druid == NULL)
        return NULL;
    druid->nb_refills = nb_refills;
    druid->pot = pot;
    return druid;
}
