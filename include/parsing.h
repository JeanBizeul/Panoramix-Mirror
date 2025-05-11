/*
** EPITECH PROJECT, 2025
** Panoramix-Mirror
** File description:
** parsing
*/

#ifndef PARSING_H_
    #define PARSING_H_

typedef struct args_s {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int nb_refills;
} args_t;

args_t *parse_panoramix_args(int argc, char **argv);

#endif /* !PARSING_H_ */
