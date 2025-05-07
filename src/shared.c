/*
** EPITECH PROJECT, 2025
** Panoramix-Mirror
** File description:
** shared
*/

#include "panoramix.h"

int Refills_left = REFILLS;

pthread_mutex_t Pot_mutex;
pthread_mutex_t Refills_left_mutex;
sem_t Potions_sem;
sem_t Call_druid_sem;
