/*
** EPITECH PROJECT, 2025
** Panoramix-Mirror
** File description:
** main
*/

#include <stdio.h>
#include "panoramix.h"

int main(void)
{
    pot_t *pot = create_pot(3);
    druid_t *druid = create_druid(3, 1, pot);
    villager_t **villagers = create_villagers(1, 5, pot);

    if (pot == NULL || druid == NULL || villagers == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 84;
    }
    if (!init_shared(3)) {
        fprintf(stderr, "Error: Initialization failed.\n");
        return 84;
    }
    launch_panoramix(villagers, druid);
    return 0;
}
