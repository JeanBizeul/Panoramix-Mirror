/*
** EPITECH PROJECT, 2025
** Panoramix-Mirror
** File description:
** villager
*/

#include <stdio.h>

#include "panoramix.h"

static bool call_pano(villager_t *villager)
{
    pthread_mutex_lock(&Refills_left_mutex);
    if (Refills_left == 0) {
        pthread_mutex_unlock(&Refills_left_mutex);
        return false;
    }
    pthread_mutex_unlock(&Refills_left_mutex);
    printf("Villager %u: Hey Pano wake up! We need more potion.\n",
        villager->id);
    sem_post(&Call_druid_sem);
    return true;
}

static void fight(villager_t *villager)
{
    villager->nb_fights--;
    printf("Villager %u: Take that roman scum! Only %u left.\n",
        villager->id, villager->nb_fights);
}

static bool wait_for_refill(villager_t *villager)
{
    bool no_more_refills = false;

    pthread_mutex_lock(&Druid_called_mutex);
    if (!Druid_called) {
        Druid_called = true;
        pthread_mutex_unlock(&Druid_called_mutex);
        if (!call_pano(villager))
            return false;
    } else {
        pthread_mutex_unlock(&Druid_called_mutex);
    }
    pthread_cond_wait(&Pot_refilled_cond, &Servings_left_mutex);
    pthread_mutex_lock(&Refills_left_mutex);
    no_more_refills = (Refills_left == 0);
    pthread_mutex_unlock(&Refills_left_mutex);
    if (Servings_left == 0 && no_more_refills) {
        pthread_mutex_unlock(&Servings_left_mutex);
        return false;
    }
    return true;
}

static bool drink(villager_t *villager)
{
    pthread_mutex_lock(&Servings_left_mutex);
    printf("Villager %u: I need a drink... I see %u servings left.\n",
        villager->id, Servings_left);
    if (Servings_left == 0) {
        if (!wait_for_refill(villager)) {
            pthread_mutex_unlock(&Servings_left_mutex);
            return false;
        }
    }
    Servings_left--;
    pthread_mutex_unlock(&Servings_left_mutex);
    return true;
}

void *village_thread(void *villager_struct)
{
    villager_t *villager = (villager_t *)villager_struct;

    printf("Villager %u: Going into battle!\n", villager->id);
    while (villager->nb_fights > 0) {
        if (!drink(villager)) {
            printf("Villager %u: I'm going to sleep now.\n", villager->id);
            break;
        }
        fight(villager);
    }
    printf("Villager %u: I'm going to sleep now.\n", villager->id);
    pthread_mutex_lock(&Villagers_done_mutex);
    Villagers_done++;
    pthread_mutex_unlock(&Villagers_done_mutex);
    return NULL;
}
