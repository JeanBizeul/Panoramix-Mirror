/*
** EPITECH PROJECT, 2025
** Panoramix-Mirror
** File description:
** parsing
*/

#include <stdlib.h>
#include <string.h>

#include "parsing.h"

args_t *parse_panoramix_args(int argc, char **argv)
{
    args_t *args = malloc(sizeof(args_t));

    if (args == NULL)
        return NULL;
    if (argc != 5) {
        free(args);
        return NULL;
    }
    args->nb_villagers = atoi(argv[1]);
    args->pot_size = atoi(argv[2]);
    args->nb_fights = atoi(argv[3]);
    args->nb_refills = atoi(argv[4]);
    if (args->nb_villagers < 0 || args->pot_size < 0
        || args->nb_fights < 0 || args->nb_refills < 0) {
        free(args);
        return NULL;
    }
    return args;
}
