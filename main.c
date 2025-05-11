/*
** EPITECH PROJECT, 2025
** Panoramix-Mirror
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>

#include "panoramix.h"
#include "parsing.h"

const char Help_msg[] =
    "USAGE: ./panoramix <nb_villagers> <pot_size>"
    " <nb_fights> <nb_refills>\n";

static bool app(args_t args) 
{
    druid_t *druid = create_druid(args.nb_refills, args.nb_villagers);
    villager_t **villagers = create_villagers(
        args.nb_villagers, args.nb_fights);

    if (druid == NULL || villagers == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return false;
    }
    if (!init_shared(args.nb_refills)) {
        fprintf(stderr, "Error: Initialization failed.\n");
        return false;
    }
    launch_panoramix(villagers, druid);
    return true;
}

int main(int argc, char **argv)
{
    args_t *parsed_args = parse_panoramix_args(argc, argv);
    bool ret = false;

    if (parsed_args == NULL) {
        fprintf(stderr, "Error: Wrong command line arguments.\n");
        fprintf(stderr, Help_msg);
        return 84;
    }
    ret = app(*parsed_args);
    free(parsed_args);
    return (ret == true ? 0 : 84);
}
